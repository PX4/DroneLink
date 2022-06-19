#include "mavlink_parameters.h"
#include "mavlink_message_handler.h"
#include "timeout_handler.h"
#include "system_impl.h"
#include <algorithm>
#include <cstring>
#include <future>

namespace mavsdk {
using namespace parameters;

MAVLinkParameters::MAVLinkParameters(
    Sender& sender,
    MavlinkMessageHandler& message_handler,
    TimeoutHandler& timeout_handler,
    TimeoutSCallback timeout_s_callback,
    bool is_server) :
    _sender(sender),
    _message_handler(message_handler),
    _timeout_handler(timeout_handler),
    _timeout_s_callback(timeout_s_callback),
    _is_server(is_server)
{
    if (const char* env_p = std::getenv("MAVSDK_PARAMETER_DEBUGGING")) {
        if (std::string(env_p) == "1") {
            LogDebug() << "Parameter debugging is on.";
            _parameter_debugging = true;
        }
    }
	// tmp debug always on
	_parameter_debugging=true;

    if (!_is_server) {
        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_VALUE,
            [this](const mavlink_message_t& message) { process_param_value(message); },
            this);

        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_EXT_VALUE,
            [this](const mavlink_message_t& message) { process_param_ext_value(message); },
            this);

        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_EXT_ACK,
            [this](const mavlink_message_t& message) { process_param_ext_ack(message); },
            this);
    }

    if (_is_server) {
        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_SET,
            [this](const mavlink_message_t& message) { process_param_set(message); },
            this);

        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_EXT_SET,
            [this](const mavlink_message_t& message) { process_param_ext_set(message); },
            this);

        // Parameter Server Callbacks
        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_REQUEST_READ,
            [this](const mavlink_message_t& message) { process_param_request_read(message); },
            this);
        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_EXT_REQUEST_READ,
            [this](const mavlink_message_t& message) { process_param_ext_request_read(message); },
            this);

        _message_handler.register_one(
            MAVLINK_MSG_ID_PARAM_REQUEST_LIST,
            [this](const mavlink_message_t& message) { process_param_request_list(message); },
            this);
        _message_handler.register_one(
                MAVLINK_MSG_ID_PARAM_EXT_REQUEST_LIST,
                [this](const mavlink_message_t& message) { process_param_ext_request_list(message); },
                this);
    }
}

MAVLinkParameters::~MAVLinkParameters()
{
    _message_handler.unregister_all(this);
}

MAVLinkParameters::Result
MAVLinkParameters::provide_server_param(const std::string& name,ParamValue param_value)
{
    assert(_is_server);
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        return Result::ParamNameTooLong;
    }
    std::lock_guard<std::mutex> lock(_all_params_mutex);
    // TODO: should we make these undefined / error cases errors ?
    if(_all_params.find(name) != _all_params.end()){
        LogDebug()<<" Providing same parameter twice:"<<name;
        const auto curr_value = _all_params.at(name);
        if(!curr_value.is_same_type(param_value)){
            LogDebug()<<"WARNING Changing type of parameter "<<name<<" from "<<curr_value.typestr()<<" to "<<param_value.typestr();
        }
    }
    _all_params.insert_or_assign(name, param_value);
    return Result::Success;
}

MAVLinkParameters::Result
MAVLinkParameters::provide_server_param_float(const std::string& name, float value)
{
    ParamValue param_value;
    param_value.set(value);
    return provide_server_param(name,param_value);
}

MAVLinkParameters::Result
MAVLinkParameters::provide_server_param_int(const std::string& name, int value)
{
    ParamValue param_value;
    param_value.set(value);
    return provide_server_param(name,param_value);
}

MAVLinkParameters::Result
MAVLinkParameters::provide_server_param_custom(const std::string& name, const std::string& value)
{
    if (value.size() > sizeof(mavlink_param_ext_set_t::param_value)) {
        LogErr() << "Error: param value too long";
        return Result::ParamValueTooLong;
    }
    ParamValue param_value;
    param_value.set(value);
    return provide_server_param(name,param_value);
}

MAVLinkParameters::Result MAVLinkParameters::set_param(
    const std::string& name,
    ParamValue value,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    assert(!_is_server);
    auto prom = std::promise<Result>();
    auto res = prom.get_future();

    set_param_async(
        name,
        value,
        [&prom](Result result) { prom.set_value(result); },
        this,
        maybe_component_id,
        extended);

    return res.get();
}

void MAVLinkParameters::set_param_async(
    const std::string& name,
    ParamValue value,
    const SetParamCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    assert(!_is_server);
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        if (callback) {
            callback(Result::ParamNameTooLong);
        }
        return;
    }
    auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Set,name,_timeout_s_callback());
    new_work->callback = callback;
    new_work->maybe_component_id = maybe_component_id;
    new_work->param_value = value;
    new_work->extended = extended;
    new_work->exact_type_known = true;
    new_work->cookie = cookie;
    _work_queue.push_back(new_work);
}

void MAVLinkParameters::set_param_int_async(
    const std::string& name,
    int32_t value,
    const SetParamCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    assert(!_is_server);
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        if (callback) {
            callback(Result::ParamNameTooLong);
        }
        return;
    }

    // PX4 only uses int32_t, so we can be sure and don't need to check the exact type first
    // by getting the param, or checking the cache.
    const bool exact_int_type_known = (_sender.autopilot() == SystemImpl::Autopilot::Px4);

    const auto set_step = [=]() {
        auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Set,name,_timeout_s_callback());
        parameters::ParamValue value_to_set;
        value_to_set.set(value);
        new_work->callback = callback;
        new_work->param_value = value_to_set;
        new_work->extended = extended;
        new_work->exact_type_known = exact_int_type_known;
        new_work->cookie = cookie;
        _work_queue.push_back(new_work);
    };

    // We need to know the exact int type first.
    if (exact_int_type_known || _all_params.find(name) != _all_params.end()) {
        // We are sure about the type, or we have it cached, we'll be able to use it.
        set_step();
    } else {
        // We don't know the exact type, so we need to get it first.
        get_param_int_async(name, nullptr, cookie, maybe_component_id, extended);
        set_step();
    }
}

MAVLinkParameters::Result MAVLinkParameters::set_param_int(
    const std::string& name,
    int32_t value,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    assert(!_is_server);
    auto prom = std::promise<Result>();
    auto res = prom.get_future();

    set_param_int_async(
        name,
        value,
        [&prom](Result result) { prom.set_value(result); },
        this,
        maybe_component_id,
        extended);

    return res.get();
}

void MAVLinkParameters::set_param_float_async(
    const std::string& name,
    float value,
    const SetParamCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
  	assert(!_is_server);
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        if (callback) {
            callback(Result::ParamNameTooLong);
        }
        return;
    }

    auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Set,name,_timeout_s_callback());
    parameters::ParamValue value_to_set;
    value_to_set.set_float(value);
    new_work->callback = callback;
    new_work->maybe_component_id = maybe_component_id;
    new_work->param_value = value_to_set;
    new_work->extended = extended;
    new_work->exact_type_known = true;
    new_work->cookie = cookie;
    _work_queue.push_back(new_work);
}

MAVLinkParameters::Result MAVLinkParameters::set_param_float(
    const std::string& name, float value, std::optional<uint8_t> maybe_component_id, bool extended)
{
  	assert(!_is_server);
    auto prom = std::promise<Result>();
    auto res = prom.get_future();

    set_param_float_async(
        name,
        value,
        [&prom](Result result) { prom.set_value(result); },
        this,
        maybe_component_id,
        extended);

    return res.get();
}

void MAVLinkParameters::set_param_custom_async(
    const std::string& name,
    const std::string& value,
    const SetParamCallback& callback,
    const void* cookie)
{
    assert(!_is_server);
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        if (callback) {
            callback(Result::ParamNameTooLong);
        }
        return;
    }

    if (value.size() > sizeof(mavlink_param_ext_set_t::param_value)) {
        LogErr() << "Error: param value too long";
        if (callback) {
            callback(Result::ParamValueTooLong);
        }
        return;
    }

    auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Set,name,_timeout_s_callback());
    parameters::ParamValue value_to_set;
    value_to_set.set_custom(value);
    new_work->callback = callback;
    new_work->param_value = value_to_set;
    new_work->extended = true;
    new_work->exact_type_known = true;
    new_work->cookie = cookie;
    _work_queue.push_back(new_work);
}

MAVLinkParameters::Result
MAVLinkParameters::set_param_custom(const std::string& name, const std::string& value)
{
    assert(!_is_server);
    auto prom = std::promise<Result>();
    auto res = prom.get_future();

    set_param_custom_async(
        name, value, [&prom](Result result) { prom.set_value(result); }, this);

    return res.get();
}

void MAVLinkParameters::get_param_async(
    const std::string& name,
    GetParamAnyCallback callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    assert(!_is_server);
    if (_parameter_debugging) {
        LogDebug() << "getting param " << name << ", extended: " << (extended ? "yes" : "no");
    }
    if (name.size() > PARAM_ID_LEN) {
        LogErr() << "Error: param name too long";
        if (callback) {
            callback(Result::ParamNameTooLong, {});
        }
        return;
    }
    // Otherwise, push work onto queue.
    auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Get,name,_timeout_s_callback());
    new_work->callback = callback;
    new_work->maybe_component_id = maybe_component_id;
    // We don't need to know the exact type when getting a value - neither extended or non-extended protocol mavlink messages
    // specify the exact type on a "get_xxx" message. This makes total sense. The client still can reason about the type and return
    // the proper error codes, it just needs to delay these checks until a response from the server has been received.
    //new_work->param_value = value;
    new_work->extended = extended;
    new_work->exact_type_known = false;
    new_work->cookie = cookie;
    _work_queue.push_back(new_work);
}

void MAVLinkParameters::get_param_async(
    const std::string& name,
    parameters::ParamValue value_type,
    const MAVLinkParameters::GetParamAnyCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    // We need to delay the type checking until we get a response from the server.
    GetParamAnyCallback callback_future_result=[callback,value_type](Result result, parameters::ParamValue value){
        if(result==Result::Success){
            if(value.is_same_type(value_type)){
                callback(Result::Success,std::move(value));
            }else{
                callback(Result::WrongType,{});
            }
        }else{
            callback(result,{});
        }
    };
    get_param_async(name,callback,cookie,maybe_component_id,extended);
}

template<class T>
void MAVLinkParameters::get_param_async_typesafe(
    const std::string& name,
    const GetParamTypesafeCallback<T> callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    // We need to delay the type checking until we get a response from the server.
    GetParamAnyCallback callback_future_result=[callback](Result result, parameters::ParamValue value){
        if(result==Result::Success){
            if(value.is_same_type_x<T>()){
                callback(Result::Success,value.get<T>());
            }else{
                callback(Result::WrongType,{});
            }
        }else{
            callback(result,{});
        }
    };
    get_param_async(name,callback_future_result,cookie,maybe_component_id,extended);
}

void MAVLinkParameters::get_param_float_async(
    const std::string& name,
    const GetParamFloatCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    get_param_async_typesafe<float>(name,callback,cookie,maybe_component_id,extended);
}


void MAVLinkParameters::get_param_int_async(
    const std::string& name,
    const GetParamIntCallback& callback,
    const void* cookie,
    std::optional<uint8_t> maybe_component_id,
    bool extended)
{
    get_param_async_typesafe<int32_t>(name,callback,cookie,maybe_component_id,extended);
}

void MAVLinkParameters::get_param_custom_async(
    const std::string& name, const GetParamCustomCallback& callback, const void* cookie,std::optional<uint8_t> maybe_component_id)
{
    get_param_async_typesafe<std::string>(name,callback,cookie,maybe_component_id,true);
}

template<class T>
std::pair<MAVLinkParameters::Result, T> MAVLinkParameters::retrieve_server_param(const std::string& name)
{
    assert(_is_server);
    std::lock_guard<std::mutex> lock(_all_params_mutex);
    if (_all_params.find(name) != _all_params.end()) {
        // This parameter exists, check its type
        const auto value = _all_params.at(name);
        if(value.is_same_type_x<T>()){
            return {MAVLinkParameters::Result::Success, value.get<T>()};
        }
        return {MAVLinkParameters::Result::WrongType, {}};
    }
    return {MAVLinkParameters::Result::NotFound, {}};
}

std::pair<MAVLinkParameters::Result, float>
MAVLinkParameters::retrieve_server_param_float(const std::string& name)
{
    return retrieve_server_param<float>(name);
}

std::pair<MAVLinkParameters::Result, std::string>
MAVLinkParameters::retrieve_server_param_custom(const std::string& name)
{
    return retrieve_server_param<std::string>(name);
}

std::pair<MAVLinkParameters::Result, int>
MAVLinkParameters::retrieve_server_param_int(const std::string& name)
{
    return retrieve_server_param<int>(name);
}

std::map<std::string, parameters::ParamValue> MAVLinkParameters::retrieve_all_server_params()
{
    assert(_is_server);
    std::lock_guard<std::mutex> lock(_all_params_mutex);
    return _all_params;
}

std::pair<MAVLinkParameters::Result, parameters::ParamValue> MAVLinkParameters::get_param(
    const std::string& name,bool extended)
{
    assert(!_is_server);
    auto prom = std::promise<std::pair<Result, ParamValue>>();
    auto res = prom.get_future();
    get_param_async(
        name,
        [&prom](Result result, ParamValue new_value) {
            prom.set_value(std::make_pair<>(result, std::move(new_value)));
        },
        this,
        extended);
    return res.get();
}

std::pair<MAVLinkParameters::Result, int32_t> MAVLinkParameters::get_param_int(
    const std::string& name, std::optional<uint8_t> maybe_component_id, bool extended)
{
    assert(!_is_server);
    auto prom = std::promise<std::pair<Result, int32_t>>();
    auto res = prom.get_future();
    get_param_int_async(
        name,
        [&prom](Result result, int32_t value) { prom.set_value(std::make_pair<>(result, value)); },
        this,
        maybe_component_id,
        extended);
    return res.get();
}

std::pair<MAVLinkParameters::Result, float> MAVLinkParameters::get_param_float(
    const std::string& name, std::optional<uint8_t> maybe_component_id, bool extended)
{
    assert(!_is_server);
    auto prom = std::promise<std::pair<Result, float>>();
    auto res = prom.get_future();
    get_param_float_async(
        name,
        [&prom](Result result, float value) { prom.set_value(std::make_pair<>(result, value)); },
        this,
        maybe_component_id,
        extended);
    return res.get();
}

std::pair<MAVLinkParameters::Result, std::string>
MAVLinkParameters::get_param_custom(const std::string& name)
{
    assert(!_is_server);
    auto prom = std::promise<std::pair<Result, std::string>>();
    auto res = prom.get_future();
    get_param_custom_async(
        name,
        [&prom](Result result, const std::string& value) {
            prom.set_value(std::make_pair<>(result, value));
        },
        this);
    return res.get();
}

void MAVLinkParameters::get_all_params_async(const GetAllParamsCallback& callback,const bool use_extended)
{
    assert(!_is_server);
    std::lock_guard<std::mutex> lock(_all_params_mutex);
    _all_params_callback = callback;
    mavlink_message_t msg;
	if(use_extended){
	  mavlink_msg_param_ext_request_list_pack(
		  _sender.get_own_system_id(),
		  _sender.get_own_component_id(),
		  &msg,
		  _sender.get_system_id(),
		  MAV_COMP_ID_AUTOPILOT1); // FIXME: what should the component be?
	}else{
	  mavlink_msg_param_request_list_pack(
		  _sender.get_own_system_id(),
		  _sender.get_own_component_id(),
		  &msg,
		  _sender.get_system_id(),
		  MAV_COMP_ID_AUTOPILOT1); // FIXME: what should the component be?
	}
    if (!_sender.send_message(msg)) {
        LogErr() << "Failed to send param list request!";
        callback(std::map<std::string, ParamValue>{});
    }
	// There are 2 possible cases - we get all the messages in time - in this case, the
	// _all_params_callback member is called. Otherwise, we get a timeout at some point, which then calls
	// the _all_params_callback member with an empty result.
    _timeout_handler.add(
        [this] { receive_timeout(); }, _timeout_s_callback(), &_all_params_timeout_cookie);
}

std::map<std::string, parameters::ParamValue> MAVLinkParameters::get_all_params(const bool use_extended)
{
    std::promise<std::map<std::string, ParamValue>> prom;
    auto res = prom.get_future();
    get_all_params_async(
		// Consti10: all_params used to be passed in here as a reference - that is a bug.
		// Since for example on a receive timeout, the empty all_params result is constructed in-place and then
		// goes out of scope when the callback returns. So don't use a reference here, pass by value or refactor the code to use
		// a std::shared_ptr.
        [&prom](std::map<std::string, parameters::ParamValue> all_params) {
            prom.set_value(all_params);
        },use_extended);
    return res.get();
}

void MAVLinkParameters::cancel_all_param(const void* cookie)
{
    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);

    for (auto item = _work_queue.begin(); item != _work_queue.end(); /* manual incrementation */) {
        if ((*item)->cookie == cookie) {
            item = _work_queue.erase(item);
        } else {
            ++item;
        }
    }
}

void MAVLinkParameters::subscribe_param_float_changed(
    const std::string& name,
    const MAVLinkParameters::ParamFloatChangedCallback& callback,
    const void* cookie)
{
    std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);

    if (callback != nullptr) {
        ParamChangedSubscription subscription{};
        subscription.param_name = name;
        subscription.callback = callback;
        subscription.cookie = cookie;
        subscription.any_type = false;
        ParamValue value_type;
        value_type.set_float(NAN);
        subscription.value_type = value_type;
        _param_changed_subscriptions.push_back(subscription);

    } else {
        for (auto it = _param_changed_subscriptions.begin();
             it != _param_changed_subscriptions.end();
             /* ++it */) {
            if (it->param_name == name && it->cookie == cookie) {
                it = _param_changed_subscriptions.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void MAVLinkParameters::subscribe_param_int_changed(
    const std::string& name,
    const MAVLinkParameters::ParamIntChangedCallback& callback,
    const void* cookie)
{
    std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);

    if (callback != nullptr) {
        ParamChangedSubscription subscription{};
        subscription.param_name = name;
        subscription.callback = callback;
        subscription.cookie = cookie;
        subscription.any_type = false;
        ParamValue value_type;
        value_type.set_int(0);
        subscription.value_type = value_type;
        _param_changed_subscriptions.push_back(subscription);

    } else {
        for (auto it = _param_changed_subscriptions.begin();
             it != _param_changed_subscriptions.end();
             /* ++it */) {
            if (it->param_name == name && it->cookie == cookie) {
                it = _param_changed_subscriptions.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void MAVLinkParameters::subscribe_param_custom_changed(
    const std::string& name,
    const MAVLinkParameters::ParamCustomChangedCallback& callback,
    const void* cookie)
{
    std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);

    if (callback != nullptr) {
        ParamChangedSubscription subscription{};
        subscription.param_name = name;
        subscription.callback = callback;
        subscription.cookie = cookie;
        subscription.any_type = false;
        ParamValue value_type;
        value_type.set_custom("");
        subscription.value_type = value_type;
        _param_changed_subscriptions.push_back(subscription);

    } else {
        for (auto it = _param_changed_subscriptions.begin();
             it != _param_changed_subscriptions.end();
             /* ++it */) {
            if (it->param_name == name && it->cookie == cookie) {
                it = _param_changed_subscriptions.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void MAVLinkParameters::do_work()
{
    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);
    auto work = work_queue_guard.get_front();

    if (!work) {
        return;
    }

    if (work->already_requested) {
        return;
    }

    char param_id[PARAM_ID_LEN + 1] = {};
    strncpy(param_id, work->param_name.c_str(), sizeof(param_id) - 1);

    uint8_t component_id = [&]() {
        if (work->maybe_component_id) {
            return work->maybe_component_id.value();
        } else {
            if (work->extended) {
                return static_cast<uint8_t>(MAV_COMP_ID_CAMERA);
            } else {
                return static_cast<uint8_t>(MAV_COMP_ID_AUTOPILOT1);
            }
        }
    }();

    switch (work->type) {
        case WorkItem::Type::Set: {
            if (!work->exact_type_known) {
                std::lock_guard<std::mutex> lock(_all_params_mutex);
                const auto it = _all_params.find(work->param_name);
                if (it == _all_params.end()) {
                    LogErr() << "Don't know the type of param_set";
                    if (std::get_if<SetParamCallback>(&work->callback)) {
                        const auto& callback = std::get<SetParamCallback>(work->callback);
                        if (callback) {
                            callback(MAVLinkParameters::Result::Failed);
                        }
                    }
                    work_queue_guard.pop_front();
                    return;
                }

                auto maybe_temp_int = work->param_value.get_int();
                if (!maybe_temp_int) {
                    // Not sure what to think when this happens.
                    LogErr() << "Error: this should definitely be an int";
                } else {
                    // First we copy over the type
                    work->param_value = it->second;
                    // And then fill in the value.
                    work->param_value.set_int(maybe_temp_int.value());
                }
            }

            if (work->extended) {
                auto param_value_buf = work->param_value.get_128_bytes();

                // FIXME: extended currently always go to the camera component
                mavlink_msg_param_ext_set_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    _sender.get_system_id(),
                    component_id,
                    param_id,
                    param_value_buf.data(),
                    work->param_value.get_mav_param_ext_type());
            } else {
			  	//LogErr() << "X1";
                float value_set = (_sender.autopilot() == SystemImpl::Autopilot::ArduPilot) ?
                                      work->param_value.get_4_float_bytes_cast() :
                                      work->param_value.get_4_float_bytes_bytewise();

                mavlink_msg_param_set_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    _sender.get_system_id(),
                    component_id,
                    param_id,
                    value_set,
                    work->param_value.get_mav_param_type());
            }

            if (!_sender.send_message(work->mavlink_message)) {
                LogErr() << "Error: Send message failed";
                if (std::get_if<SetParamCallback>(&work->callback)) {
                    const auto& callback = std::get<SetParamCallback>(work->callback);
                    if (callback) {
                        callback(MAVLinkParameters::Result::ConnectionError);
                    }
                }
                work_queue_guard.pop_front();
                return;
            }

            work->already_requested = true;
            // _last_request_time = _sender.get_time().steady_time();

            // We want to get notified if a timeout happens
            _timeout_handler.add([this] { receive_timeout(); }, work->timeout_s, &_timeout_cookie);

        } break;

        case WorkItem::Type::Get: {
            // LogDebug() << "now getting: " << work->param_name;
            if (work->extended) {
                mavlink_msg_param_ext_request_read_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    _sender.get_system_id(),
                    component_id,
                    param_id,
                    -1);

            } else {
                // LogDebug() << "request read: "
                //    << (int)_sender.get_own_system_id() << ":"
                //    << (int)_sender.get_own_component_id() <<
                //    " to "
                //    << (int)_sender.get_system_id() << ":"
                //    << (int)_sender.get_autopilot_id();

                mavlink_msg_param_request_read_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    _sender.get_system_id(),
                    component_id,
                    param_id,
                    -1);
            }

            if (!_sender.send_message(work->mavlink_message)) {
                LogErr() << "Error: Send message failed";
               if (std::get_if<GetParamAnyCallback>(&work->callback)) {
                   const auto& callback = std::get<GetParamAnyCallback>(work->callback);
                    if (callback) {
                        (callback)(Result::ConnectionError, ParamValue{});
                    }
                }
                work_queue_guard.pop_front();
                return;
            }

            work->already_requested = true;

            // _last_request_time = _sender.get_time().steady_time();

            // We want to get notified if a timeout happens
            _timeout_handler.add([this] { receive_timeout(); }, work->timeout_s, &_timeout_cookie);

        } break;

        case WorkItem::Type::Value: {
            if (work->extended) {
                auto buf = work->param_value.get_128_bytes();
                mavlink_msg_param_ext_value_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    param_id,
                    buf.data(),
                    work->param_value.get_mav_param_ext_type(),
                    work->param_count,
                    work->param_index);
            } else {
                float param_value;
                if (_sender.autopilot() == SystemImpl::Autopilot::ArduPilot) {
                    param_value = work->param_value.get_4_float_bytes_cast();
                } else {
                    param_value = work->param_value.get_4_float_bytes_bytewise();
                }
                mavlink_msg_param_value_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    param_id,
                    param_value,
                    work->param_value.get_mav_param_type(),
                    work->param_count,
                    work->param_index);
            }

            if (!_sender.send_message(work->mavlink_message)) {
                LogErr() << "Error: Send message failed";
                work_queue_guard.pop_front();
                return;
            }

            // As we're a server in this case we don't need any response
            work_queue_guard.pop_front();
        } break;

        case WorkItem::Type::Ack: {
            if (work->extended) {
                auto buf = work->param_value.get_128_bytes();
                mavlink_msg_param_ext_ack_pack(
                    _sender.get_own_system_id(),
                    _sender.get_own_component_id(),
                    &work->mavlink_message,
                    param_id,
                    buf.data(),
                    work->param_value.get_mav_param_ext_type(),
                    PARAM_ACK_ACCEPTED);
            }

            if (!work->extended || !_sender.send_message(work->mavlink_message)) {
                LogErr() << "Error: Send message failed";
                work_queue_guard.pop_front();
                return;
            }

            // As we're a server in this case we don't need any response
            work_queue_guard.pop_front();
        } break;
    }
}

void MAVLinkParameters::process_param_value(const mavlink_message_t& message)
{
    mavlink_param_value_t param_value;
    mavlink_msg_param_value_decode(&message, &param_value);

    if (_parameter_debugging) {
        LogDebug() << "getting param value: " << extract_safe_param_id(param_value.param_id);
    }

    ParamValue received_value;
    if (_sender.autopilot() == SystemImpl::Autopilot::ArduPilot) {
        received_value.set_from_mavlink_param_value_cast(param_value);
    } else {
        received_value.set_from_mavlink_param_value_bytewise(param_value);
    }

    const std::string param_id = extract_safe_param_id(param_value.param_id);

    {
        std::lock_guard<std::mutex> lock(_all_params_mutex);
        _all_params[param_id] = received_value;

        // check if we are looking for param list (get all parameters).
        if (_all_params_callback) {
			// If we are currently waiting for all parameters, this is a hacky way to basically say
			// "Hey, we got the last parameter, so we got all parameters, and can forward that to the user."
			// Note that I don't think this accounts for the case where a parameter that is not the last parameter went missing.
			// So it is better than nothing, but also not ideal. Correct me if I'm wrong.
            if (param_value.param_index + 1 == param_value.param_count) {
                _timeout_handler.remove(_all_params_timeout_cookie);
                _all_params_callback(_all_params);
                _all_params_callback = nullptr;
            } else {
                _timeout_handler.remove(_all_params_timeout_cookie);

                _timeout_handler.add(
                    [this] { receive_timeout(); },
                    _timeout_s_callback(),
                    &_all_params_timeout_cookie);
            }

            return;
        }
    }

    notify_param_subscriptions(param_value);

    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);
    auto work = work_queue_guard.get_front();

    if (!work) {
        return;
    }

    if (!work->already_requested) {
        return;
    }

    if (work->param_name != extract_safe_param_id(param_value.param_id)) {
        // No match, let's just return the borrowed work item.
        return;
    }

    switch (work->type) {
        case WorkItem::Type::Get: {
            if (std::get_if<GetParamAnyCallback>(&work->callback)) {
                const auto& callback = std::get<GetParamAnyCallback>(work->callback);
                if (callback) {
                    callback(Result::Success, received_value);
                }
            }
            _timeout_handler.remove(_timeout_cookie);
            // LogDebug() << "time taken: " <<
            // _sender.get_time().elapsed_since_s(_last_request_time);
            work_queue_guard.pop_front();
        } break;
        case WorkItem::Type::Set: {
            // We are done, inform caller and go back to idle
            if (std::get_if<SetParamCallback>(&work->callback)) {
                const auto& callback = std::get<SetParamCallback>(work->callback);
                if (callback) {
                    callback(MAVLinkParameters::Result::Success);
                }
            }

            _timeout_handler.remove(_timeout_cookie);
            // LogDebug() << "time taken: " <<
            // _sender.get_time().elapsed_since_s(_last_request_time);
            work_queue_guard.pop_front();
        } break;
        default:
            break;
    }
}

void MAVLinkParameters::notify_param_subscriptions(const mavlink_param_value_t& param_value)
{
    std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);

    for (const auto& subscription : _param_changed_subscriptions) {
        if (subscription.param_name != extract_safe_param_id(param_value.param_id)) {
            continue;
        }

        ParamValue value;

        if (_sender.autopilot() == SystemImpl::Autopilot::ArduPilot) {
            value.set_from_mavlink_param_value_cast(param_value);
        } else {
            value.set_from_mavlink_param_value_bytewise(param_value);
        }

        if (!subscription.any_type && !subscription.value_type.is_same_type(value)) {
            LogErr() << "Received wrong param type in subscription for " << subscription.param_name;
            continue;
        }

        call_param_changed_callback(subscription.callback, value);
    }
}

void MAVLinkParameters::process_param_ext_value(const mavlink_message_t& message)
{
    if (_parameter_debugging) {
        LogDebug() << "getting param ext value";
    }

    mavlink_param_ext_value_t param_ext_value{};
    mavlink_msg_param_ext_value_decode(&message, &param_ext_value);

    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);
    auto work = work_queue_guard.get_front();

    if (!work) {
        return;
    }

    if (!work->already_requested) {
        return;
    }

    if (work->param_name != extract_safe_param_id(param_ext_value.param_id)) {
        return;
    }

    switch (work->type) {
        case WorkItem::Type::Get: {
            ParamValue value;
            value.set_from_mavlink_param_ext_value(param_ext_value);
            if (std::get_if<GetParamAnyCallback>(&work->callback)) {
                const auto& callback = std::get<GetParamAnyCallback>(work->callback);
                if (callback) {
                    callback(Result::Success,value);
                }
            }
            _timeout_handler.remove(_timeout_cookie);
            // LogDebug() << "time taken: " <<
            // _sender.get_time().elapsed_since_s(_last_request_time);
            work_queue_guard.pop_front();
        } break;

        case WorkItem::Type::Set:
            LogWarn() << "Unexpected ParamExtValue response";
            break;
        default:
            break;
    }
}

void MAVLinkParameters::process_param_ext_ack(const mavlink_message_t& message)
{
    // LogDebug() << "getting param ext ack";

    mavlink_param_ext_ack_t param_ext_ack;
    mavlink_msg_param_ext_ack_decode(&message, &param_ext_ack);

    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);
    auto work = work_queue_guard.get_front();

    if (!work) {
        return;
    }

    if (!work->already_requested) {
        return;
    }

    // Now it still needs to match the param name
    if (work->param_name != extract_safe_param_id(param_ext_ack.param_id)) {
        return;
    }

    switch (work->type) {
        case WorkItem::Type::Get: {
            LogWarn() << "Unexpected ParamExtAck response.";
        } break;

        case WorkItem::Type::Set: {
            if (param_ext_ack.param_result == PARAM_ACK_ACCEPTED) {
                // We are done, inform caller and go back to idle
                if (std::get_if<SetParamCallback>(&work->callback)) {
                    const auto& callback = std::get<SetParamCallback>(work->callback);
                    if (callback) {
                        callback(MAVLinkParameters::Result::Success);
                    }
                }

                _timeout_handler.remove(_timeout_cookie);
                // LogDebug() << "time taken: " <<
                // _sender.get_time().elapsed_since_s(_last_request_time);
                work_queue_guard.pop_front();

            } else if (param_ext_ack.param_result == PARAM_ACK_IN_PROGRESS) {
                // Reset timeout and wait again.
                _timeout_handler.refresh(_timeout_cookie);

            } else {
                LogErr() << "Somehow we did not get an ack, we got: "
                         << int(param_ext_ack.param_result);

                if (std::get_if<SetParamCallback>(&work->callback)) {
                    const auto& callback = std::get<SetParamCallback>(work->callback);
                    if (callback) {
                        auto result = [&]() {
                            switch (param_ext_ack.param_result) {
                                case PARAM_ACK_FAILED:
                                    return MAVLinkParameters::Result::Failed;
                                case PARAM_ACK_VALUE_UNSUPPORTED:
                                    return MAVLinkParameters::Result::ValueUnsupported;
                                default:
                                    return MAVLinkParameters::Result::UnknownError;
                            }
                        }();
                        callback(result);
                    }
                }

                _timeout_handler.remove(_timeout_cookie);
                // LogDebug() << "time taken: " <<
                // _sender.get_time().elapsed_since_s(_last_request_time);
                work_queue_guard.pop_front();
            }
        } break;
        default:
            break;
    }
}

void MAVLinkParameters::process_param_ext_set(const mavlink_message_t& message)
{
    mavlink_param_ext_set_t set_request{};
    mavlink_msg_param_ext_set_decode(&message, &set_request);

    const std::string safe_param_id = extract_safe_param_id(set_request.param_id);
    if (!safe_param_id.empty()) {
        LogDebug() << "Set Param Request: " << safe_param_id;
        {
            // Use the ID
            std::lock_guard<std::mutex> lock(_all_params_mutex);
		  	parameters::ParamValue value{};
            if (!value.set_from_mavlink_param_ext_set(set_request)) {
                LogWarn() << "Invalid Param Ext Set Request: " << safe_param_id;
                return;
            }
            _all_params[safe_param_id] = value;
        }

        auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Ack,safe_param_id,_timeout_s_callback());
        new_work->param_value = _all_params[safe_param_id];
        new_work->extended = true;
        _work_queue.push_back(new_work);
        std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);

        for (const auto& subscription : _param_changed_subscriptions) {
            if (subscription.param_name != safe_param_id) {
                continue;
            }

            if (!subscription.any_type &&
                !subscription.value_type.is_same_type(new_work->param_value)) {
                LogErr() << "Received wrong param type in subscription for "
                         << subscription.param_name;
                continue;
            }

            call_param_changed_callback(subscription.callback, new_work->param_value);
        }
    } else {
        LogWarn() << "Invalid Param Ext Set ID Request: " << safe_param_id;
    }
}

void MAVLinkParameters::receive_timeout()
{
    {
        std::lock_guard<std::mutex> lock(_all_params_mutex);
        // first check if we are waiting for param list response
        if (_all_params_callback) {
		  	LogDebug()<<"All params receive timeout";
            _all_params_callback({});
            return;
        }
    }

    LockedQueue<WorkItem>::Guard work_queue_guard(_work_queue);
    auto work = work_queue_guard.get_front();

    if (!work) {
        LogErr() << "Received timeout without work";
        return;
    }

    if (!work->already_requested) {
        return;
    }

    switch (work->type) {
        case WorkItem::Type::Get: {
            parameters::ParamValue empty_value;
            if (work->retries_to_do > 0) {
                // We're not sure the command arrived, let's retransmit.
                LogWarn() << "sending again, retries to do: " << work->retries_to_do << "  ("
                          << work->param_name << ").";
                if (!_sender.send_message(work->mavlink_message)) {
                    LogErr() << "connection send error in retransmit (" << work->param_name << ").";
                    work_queue_guard.pop_front();

                    if (std::get_if<GetParamAnyCallback>(&work->callback)) {
                        const auto& callback = std::get<GetParamAnyCallback>(work->callback);
                        if (callback) {
                            callback(Result::ConnectionError, {});
                        }
                    }
                } else {
                    --work->retries_to_do;
                    _timeout_handler.add(
                        [this] { receive_timeout(); }, work->timeout_s, &_timeout_cookie);
                }
            } else {
                // We have tried retransmitting, giving up now.
                LogErr() << "Error: Retrying failed get param busy timeout: " << work->param_name;

                work_queue_guard.pop_front();

                if (std::get_if<GetParamAnyCallback>(&work->callback)) {
                    const auto& callback = std::get<GetParamAnyCallback>(work->callback);
                    if (callback) {
                        callback(Result::Timeout, {});
                    }
                }
            }
        } break;
        case WorkItem::Type::Set: {
            if (work->retries_to_do > 0) {
                // We're not sure the command arrived, let's retransmit.
                LogWarn() << "sending again, retries to do: " << work->retries_to_do << "  ("
                          << work->param_name << ").";
                if (!_sender.send_message(work->mavlink_message)) {
                    LogErr() << "connection send error in retransmit (" << work->param_name << ").";
                    work_queue_guard.pop_front();
                    if (std::get_if<SetParamCallback>(&work->callback)) {
                        const auto& callback = std::get<SetParamCallback>(work->callback);
                        if (callback) {
                            callback(MAVLinkParameters::Result::ConnectionError);
                        }
                    }
                } else {
                    --work->retries_to_do;
                    _timeout_handler.add(
                        [this] { receive_timeout(); }, work->timeout_s, &_timeout_cookie);
                }
            } else {
                // We have tried retransmitting, giving up now.
                LogErr() << "Error: Retrying failed get param busy timeout: " << work->param_name;

                work_queue_guard.pop_front();
                if (std::get_if<SetParamCallback>(&work->callback)) {
                    const auto& callback = std::get<SetParamCallback>(work->callback);
                    if (callback) {
                        callback(MAVLinkParameters::Result::Timeout);
                    }
                }
            }
        } break;
        default:
            break;
    }
}

std::string MAVLinkParameters::extract_safe_param_id(const char param_id[])
{
    // The param_id field of the MAVLink struct has length 16 and is not 0 terminated.
    // Therefore, we make a 0 terminated copy first.
    char param_id_long_enough[PARAM_ID_LEN + 1] = {};
    std::memcpy(param_id_long_enough, param_id, PARAM_ID_LEN);
    return {param_id_long_enough};
}

void MAVLinkParameters::process_param_set(const mavlink_message_t& message)
{
    mavlink_param_set_t set_request{};
    mavlink_msg_param_set_decode(&message, &set_request);

    const std::string safe_param_id = extract_safe_param_id(set_request.param_id);
    if (!safe_param_id.empty()) {
        LogDebug() << "Set Param Request: " << safe_param_id << " with value "
                   << *(int32_t*)(&set_request.param_value);

        // Use the ID
        if (_all_params.find(safe_param_id) != _all_params.end()) {
		  	parameters::ParamValue value{};
            if (!value.set_from_mavlink_param_set_bytewise(set_request)) {
                LogWarn() << "Invalid Param Set Request: " << safe_param_id;
                return;
            }

            LogDebug() << "Changing param from " << _all_params[safe_param_id] << " to " << value;
            _all_params[safe_param_id] = value;

            auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Value,safe_param_id,_timeout_s_callback());
            new_work->param_value = _all_params.at(safe_param_id);
            new_work->extended = false;
            _work_queue.push_back(new_work);
            std::lock_guard<std::mutex> lock(_param_changed_subscriptions_mutex);
            for (const auto& subscription : _param_changed_subscriptions) {
                if (subscription.param_name != safe_param_id) {
                    continue;
                }
                if (!subscription.any_type && !subscription.value_type.is_same_type(value)) {
                    LogErr() << "Received wrong param type in subscription for "
                             << subscription.param_name;
                    continue;
                }

                call_param_changed_callback(subscription.callback, value);
            }
        } else {
            LogDebug() << "Missing Param: " << safe_param_id << "(this: " << this << ")";
        }
    } else {
        LogWarn() << "Invalid Param Set ID Request: " << safe_param_id;
    }
}

void MAVLinkParameters::call_param_changed_callback(
    const ParamChangedCallbacks& callback, const ParamValue& value)
{
    if (std::get_if<ParamFloatChangedCallback>(&callback) && value.get_float()) {
        std::get<ParamFloatChangedCallback>(callback)(value.get_float().value());

    } else if (std::get_if<ParamIntChangedCallback>(&callback) && value.get_int()) {
        std::get<ParamIntChangedCallback>(callback)(value.get_int().value());

    } else if (std::get_if<ParamCustomChangedCallback>(&callback) && value.get_custom()) {
        std::get<ParamCustomChangedCallback>(callback)(value.get_custom().value());
    } else {
        LogErr() << "Type and callback mismatch";
    }
}

void MAVLinkParameters::process_param_request_read(const mavlink_message_t& message)
{
    mavlink_param_request_read_t read_request{};
    mavlink_msg_param_request_read_decode(&message, &read_request);

    if (read_request.param_index == -1) {
        const auto safe_param_id= extract_safe_param_id(read_request.param_id);
        LogDebug() << "Request Param " << safe_param_id;

        // Use the ID
        if (_all_params.find(safe_param_id) != _all_params.end()) {
		   // Make sure we are not forwarding an extended param via the "normal" param messages.
		   const auto param_value= _all_params.at(safe_param_id);
			if(param_value.needs_extended()){
			  LogDebug()<<"Not forwarding param"<<safe_param_id<<" since it needs extended";
			  return;
			}
            auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Value,safe_param_id,_timeout_s_callback());
            new_work->param_value = _all_params.at(safe_param_id);
            new_work->extended = false;
            _work_queue.push_back(new_work);
        } else {
            LogDebug() << "Missing Param " << safe_param_id;
        }
    }
}

void MAVLinkParameters::process_param_request_list(const mavlink_message_t& message)
{
    mavlink_param_request_list_t list_request{};
    mavlink_msg_param_request_list_decode(&message, &list_request);
	int idx=0;
    for (const auto& pair : _all_params) {
	  	// make sure extended parameters never make it out via the param request list
		// (use param extended list)
		if(pair.second.needs_extended()){
		  LogDebug()<<"Not forwarding param"<<pair.first<<" since it needs extended";
		  continue;
		}
        auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Value,pair.first,_timeout_s_callback());
        new_work->param_value = pair.second;
        new_work->extended = false;
		// Consti10 - the count of parameters when queried from a non-ext perspective is different, since we need to hide the parameters
		// that need the extended protocol
        //new_work->param_count = static_cast<int>(_all_params.size());
		new_work->param_count = get_current_parameters_count(false);
        new_work->param_index = idx++;
        _work_queue.push_back(new_work);
    }
}

void MAVLinkParameters::process_param_ext_request_list(const mavlink_message_t& message)
{
  mavlink_param_ext_request_list_t ext_list_request{};
  mavlink_msg_param_ext_request_list_decode(&message, &ext_list_request);
  int idx=0;
  for (const auto& pair : _all_params) {
	auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Value,pair.first,_timeout_s_callback());
	new_work->param_value = pair.second;
	new_work->extended = true;
	new_work->param_count = get_current_parameters_count(true);
	new_work->param_index = idx++;
	_work_queue.push_back(new_work);
  }
}

void MAVLinkParameters::process_param_ext_request_read(const mavlink_message_t& message)
{
    mavlink_param_request_read_t read_request{};
    mavlink_msg_param_request_read_decode(&message, &read_request);

    if (read_request.param_index == -1) {
        const auto safe_param_id = extract_safe_param_id(read_request.param_id);
        LogDebug() << "Request Param " << safe_param_id;
        // Use the ID
        if (_all_params.find(safe_param_id) != _all_params.end()) {
            auto new_work = std::make_shared<WorkItem>(WorkItem::Type::Value,safe_param_id,_timeout_s_callback());
            new_work->param_value = _all_params.at(safe_param_id);
            new_work->extended = true;
            _work_queue.push_back(new_work);
        } else {
            LogDebug() << "Missing Param " << safe_param_id;
        }
    }
}

std::ostream& operator<<(std::ostream& str, const MAVLinkParameters::Result& result)
{
    switch (result) {
        case MAVLinkParameters::Result::Success:
            return str << "Success";
        case MAVLinkParameters::Result::Timeout:
            return str << "Timeout";
        case MAVLinkParameters::Result::ConnectionError:
            return str << "ConnectionError";
        case MAVLinkParameters::Result::WrongType:
            return str << "WrongType";
        case MAVLinkParameters::Result::ParamNameTooLong:
            return str << "ParamNameTooLong";
        case MAVLinkParameters::Result::NotFound:
            return str << "NotFound";
        case MAVLinkParameters::Result::ValueUnsupported:
            return str << "ValueUnsupported";
        case MAVLinkParameters::Result::Failed:
            return str << "Failed";
        case MAVLinkParameters::Result::UnknownError:
            // Fallthrough
        default:
            return str << "UnknownError";
    }
}

int MAVLinkParameters::get_current_parameters_count(bool extended)const{
  if(extended){
	// easy, we can do all parameters.
	return static_cast<int>(_all_params.size());
  }
  // a bit messy, we need to loop through all params and only count the ones that are non-extended
  int count=0;
  for (auto const& [key, val] : _all_params){
	if(!val.needs_extended()){
	  count++;
	}
  }
  return count;
}


} // namespace mavsdk
