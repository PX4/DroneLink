#include "action_impl.h"
#include "mavsdk_impl.h"
#include "mavsdk_math.h"
#include "flight_mode.h"
#include "px4_custom_mode.h"
#include <cmath>
#include <future>

namespace mavsdk {

ActionImpl::ActionImpl(System& system) : PluginImplBase(system)
{
    _parent->register_plugin(this);
}

ActionImpl::ActionImpl(std::shared_ptr<System> system) : PluginImplBase(std::move(system))
{
    _parent->register_plugin(this);
}

ActionImpl::~ActionImpl()
{
    _parent->unregister_plugin(this);
}

void ActionImpl::init()
{
    // We need the system state.
    _parent->register_mavlink_message_handler(
        MAVLINK_MSG_ID_EXTENDED_SYS_STATE,
        [this](const mavlink_message_t& message) { process_extended_sys_state(message); },
        this);
}

void ActionImpl::deinit()
{
    _parent->unregister_all_mavlink_message_handlers(this);
}

void ActionImpl::enable()
{
    // And we need to make sure the system state is actually sent.
    // We use the async call here because we should not block in the init call because
    // we won't receive an answer anyway in init because the receive loop is not
    // called while we are being created here.
    _parent->set_msg_rate_async(
        MAVLINK_MSG_ID_EXTENDED_SYS_STATE,
        1.0,
        nullptr,
        MavlinkCommandSender::DEFAULT_COMPONENT_ID_AUTOPILOT);
}

void ActionImpl::disable() {}

Action::Result ActionImpl::arm() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    arm_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::disarm() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    disarm_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::terminate() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    terminate_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::kill() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    kill_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::reboot() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    reboot_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::shutdown() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    shutdown_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::takeoff() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    takeoff_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::land() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    land_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::return_to_launch() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    return_to_launch_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::goto_location(
    const double latitude_deg,
    const double longitude_deg,
    const float altitude_amsl_m,
    const float yaw_deg)
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    goto_location_async(
        latitude_deg, longitude_deg, altitude_amsl_m, yaw_deg, [&prom](Action::Result result) {
            prom.set_value(result);
        });

    return fut.get();
}

Action::Result ActionImpl::do_orbit(
    const float radius_m,
    const float velocity_ms,
    const Action::OrbitYawBehavior yaw_behavior,
    const double latitude_deg,
    const double longitude_deg,
    const double absolute_altitude_m)
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    do_orbit_async(
        radius_m,
        velocity_ms,
        yaw_behavior,
        latitude_deg,
        longitude_deg,
        absolute_altitude_m,
        [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::hold() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    hold_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::set_actuator(const int index, const float value)
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    set_actuator_async(index, value, [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::transition_to_fixedwing() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    transition_to_fixedwing_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::transition_to_multicopter() const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    transition_to_multicopter_async([&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

void ActionImpl::arm_async(const Action::ResultCallback& callback) const
{
    auto send_arm_command = [this, callback]() {
        MavlinkCommandSender::CommandLong command{};

        command.command = MAV_CMD_COMPONENT_ARM_DISARM;
        command.params.maybe_param1 = 1.0f; // arm
        command.target_component_id = _parent->get_autopilot_id();

        _parent->send_command_async(
            command, [this, callback](MavlinkCommandSender::Result result, float) {
                command_result_callback(result, callback);
            });
    };

    if (need_hold_before_arm()) {
        _parent->set_flight_mode_async(
            FlightMode::Hold,
            [callback, send_arm_command](MavlinkCommandSender::Result result, float) {
                Action::Result action_result = action_result_from_command_result(result);
                if (action_result != Action::Result::Success) {
                    if (callback) {
                        callback(action_result);
                    }
                }
                send_arm_command();
            });
        return;
    } else {
        send_arm_command();
    }
}

bool ActionImpl::need_hold_before_arm() const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        return need_hold_before_arm_px4();
    } else {
        return need_hold_before_arm_apm();
    }
}

bool ActionImpl::need_hold_before_arm_px4() const
{
    if (_parent->get_flight_mode() == FlightMode::Mission ||
        _parent->get_flight_mode() == FlightMode::ReturnToLaunch) {
        return true;
    } else {
        return false;
    }
}

bool ActionImpl::need_hold_before_arm_apm() const
{
    if (_parent->get_flight_mode() == FlightMode::Mission ||
        _parent->get_flight_mode() == FlightMode::ReturnToLaunch ||
        _parent->get_flight_mode() == FlightMode::Land) {
        return true;
    } else {
        return false;
    }
}

void ActionImpl::disarm_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_COMPONENT_ARM_DISARM;
    command.params.maybe_param1 = 0.0f; // disarm
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::terminate_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_DO_FLIGHTTERMINATION;
    command.params.maybe_param1 = 1.0f;
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::kill_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_COMPONENT_ARM_DISARM;
    command.params.maybe_param1 = 0.0f; // kill
    command.params.maybe_param2 = 21196.f; // magic number to enforce in-air
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::reboot_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN;
    command.params.maybe_param1 = 1.0f; // reboot autopilot
    command.params.maybe_param2 = 1.0f; // reboot onboard computer
    command.params.maybe_param3 = 1.0f; // reboot component
    command.params.maybe_param4 = 0.0f; // all components
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::shutdown_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN;
    command.params.maybe_param1 = 2.0f; // shutdown autopilot
    command.params.maybe_param2 = 2.0f; // shutdown onboard computer
    command.params.maybe_param3 = 2.0f; // shutdown component
    command.params.maybe_param4 = 0.0f; // all components
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::takeoff_async(const Action::ResultCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        takeoff_async_px4(callback);
    } else {
        takeoff_async_apm(callback);
    }
}

void ActionImpl::takeoff_async_px4(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_NAV_TAKEOFF;
    command.target_component_id = _parent->get_autopilot_id();

    command.params.maybe_param7 = get_takeoff_altitude().second;

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::takeoff_async_apm(const Action::ResultCallback& callback) const
{
    auto send_takeoff_command = [this, callback]() {
        MavlinkCommandSender::CommandLong command{};

        command.command = MAV_CMD_NAV_TAKEOFF;
        command.target_component_id = _parent->get_autopilot_id();
        command.params.maybe_param7 = get_takeoff_altitude().second;

        _parent->send_command_async(
            command, [this, callback](MavlinkCommandSender::Result result, float) {
                command_result_callback(result, callback);
            });
    };
    if (_parent->get_flight_mode() != FlightMode::Offboard) {
        _parent->set_flight_mode_async(
            FlightMode::Offboard,
            [callback, send_takeoff_command](MavlinkCommandSender::Result result, float) {
                Action::Result action_result = action_result_from_command_result(result);
                if (action_result != Action::Result::Success) {
                    if (callback) {
                        callback(action_result);
                    }
                }
                send_takeoff_command();
            });
    } else {
        send_takeoff_command();
    }
}

void ActionImpl::land_async(const Action::ResultCallback& callback) const
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_NAV_LAND;
    command.params.maybe_param4 = NAN; // Don't change yaw.
    command.target_component_id = _parent->get_autopilot_id();

    // We don't know the altitude of the landing spot, so we don't set it.

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::return_to_launch_async(const Action::ResultCallback& callback) const
{
    _parent->set_flight_mode_async(
        FlightMode::ReturnToLaunch, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::goto_location_async(
    const double latitude_deg,
    const double longitude_deg,
    const float altitude_amsl_m,
    const float yaw_deg,
    const Action::ResultCallback& callback)
{
    auto send_do_reposition =
        [this, callback, yaw_deg, latitude_deg, longitude_deg, altitude_amsl_m]() {
            MavlinkCommandSender::CommandInt command{};

            command.command = MAV_CMD_DO_REPOSITION;
            command.target_component_id = _parent->get_autopilot_id();
            command.params.maybe_param2 = static_cast<float>(MAV_DO_REPOSITION_FLAGS_CHANGE_MODE);
            command.params.maybe_param4 = static_cast<float>(to_rad_from_deg(yaw_deg));
            command.params.x = int32_t(std::round(latitude_deg * 1e7));
            command.params.y = int32_t(std::round(longitude_deg * 1e7));
            command.params.maybe_z = altitude_amsl_m;

            _parent->send_command_async(
                command, [this, callback](MavlinkCommandSender::Result result, float) {
                    command_result_callback(result, callback);
                });
        };

    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // Change to Hold mode first
        if (_parent->get_flight_mode() != FlightMode::Hold) {
            _parent->set_flight_mode_async(
                FlightMode::Hold,
                [this, callback, send_do_reposition](MavlinkCommandSender::Result result, float) {
                    Action::Result action_result = action_result_from_command_result(result);
                    if (action_result != Action::Result::Success) {
                        command_result_callback(result, callback);
                        return;
                    }
                    send_do_reposition();
                });
            return;
        }
    }

    send_do_reposition();
}

void ActionImpl::do_orbit_async(
    const float radius_m,
    const float velocity_ms,
    const Action::OrbitYawBehavior yaw_behavior,
    const double latitude_deg,
    const double longitude_deg,
    const double absolute_altitude_m,
    const Action::ResultCallback& callback)
{
    // The DO_ORBIT command is marked as WIP, hence only supported for PX4 for now.
    if (_parent->compatibility_mode() != System::CompatibilityMode::Px4) {
        _parent->call_user_callback([callback]() { callback(Action::Result::Unsupported); });
    }

    MavlinkCommandSender::CommandInt command{};
    command.command = MAV_CMD_DO_ORBIT;
    command.target_component_id = _parent->get_autopilot_id();
    command.params.maybe_param1 = radius_m;
    command.params.maybe_param2 = velocity_ms;
    command.params.maybe_param3 = static_cast<float>(yaw_behavior);
    command.params.x = int32_t(std::round(latitude_deg * 1e7));
    command.params.y = int32_t(std::round(longitude_deg * 1e7));
    command.params.maybe_z = static_cast<float>(absolute_altitude_m);

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::hold_async(const Action::ResultCallback& callback) const
{
    _parent->set_flight_mode_async(
        FlightMode::Hold, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::set_actuator_async(
    const int index, const float value, const Action::ResultCallback& callback)
{
    // TODO: improve the API to accept multiple actuators.
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_DO_SET_ACTUATOR;
    command.target_component_id = _parent->get_autopilot_id();

    switch (index % 6) {
        case 1:
            command.params.maybe_param1 = value;
            break;
        case 2:
            command.params.maybe_param2 = value;
            break;
        case 3:
            command.params.maybe_param3 = value;
            break;
        case 4:
            command.params.maybe_param4 = value;
            break;
        case 5:
            command.params.maybe_param5 = value;
            break;
        case 6:
            command.params.maybe_param6 = value;
            break;
    }
    command.params.maybe_param7 = static_cast<float>(index) / 6.0f;

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::transition_to_fixedwing_async(const Action::ResultCallback& callback) const
{
    if (!_vtol_transition_support_known) {
        if (callback) {
            _parent->call_user_callback(
                [callback]() { callback(Action::Result::VtolTransitionSupportUnknown); });
        }
        return;
    }

    if (!_vtol_transition_possible) {
        if (callback) {
            _parent->call_user_callback(
                [callback]() { callback(Action::Result::NoVtolTransitionSupport); });
        }
        return;
    }

    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_DO_VTOL_TRANSITION;
    command.params.maybe_param1 = static_cast<float>(MAV_VTOL_STATE_FW);
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::transition_to_multicopter_async(const Action::ResultCallback& callback) const
{
    if (!_vtol_transition_support_known) {
        if (callback) {
            callback(Action::Result::VtolTransitionSupportUnknown);
        }
        return;
    }

    if (!_vtol_transition_possible) {
        if (callback) {
            callback(Action::Result::NoVtolTransitionSupport);
        }
        return;
    }
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_DO_VTOL_TRANSITION;
    command.params.maybe_param1 = static_cast<float>(MAV_VTOL_STATE_MC);
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

void ActionImpl::process_extended_sys_state(const mavlink_message_t& message)
{
    mavlink_extended_sys_state_t extended_sys_state;
    mavlink_msg_extended_sys_state_decode(&message, &extended_sys_state);

    if (extended_sys_state.vtol_state != MAV_VTOL_STATE_UNDEFINED) {
        _vtol_transition_possible = true;
    } else {
        _vtol_transition_possible = false;
    }
    _vtol_transition_support_known = true;
}

void ActionImpl::set_takeoff_altitude_async(
    const float relative_altitude_m, const Action::ResultCallback& callback)
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // For PX4 we have to access the param as of 2022-03.
        // TODO: change at some point in the future
        _parent->set_param_float_async(
            TAKEOFF_ALT_PARAM,
            relative_altitude_m,
            [callback, this](MAVLinkParameters::Result result) {
                _parent->call_user_callback([callback, result] {
                    callback(
                        (result == MAVLinkParameters::Result::Success) ?
                            Action::Result::Success :
                            Action::Result::ParameterError);
                });
            },
            this);

    } else {
        _takeoff_altitude = relative_altitude_m;
        _parent->call_user_callback([callback]() { callback(Action::Result::Success); });
    }
}

Action::Result ActionImpl::set_takeoff_altitude(float relative_altitude_m)
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    set_takeoff_altitude_async(
        relative_altitude_m, [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::set_takeoff_altitude_apm(float relative_altitude_m)
{
    _takeoff_altitude = relative_altitude_m;
    return Action::Result::Success;
}

void ActionImpl::get_takeoff_altitude_async(
    const Action::GetTakeoffAltitudeCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // When using with PX4 we use the param which will give the correct result for now.
        // That's because PX4 as of 2022-03 does not support takeoff altitude as part of
        // the command param.
        // TODO: change at some point in the future
        _parent->get_param_float_async(
            TAKEOFF_ALT_PARAM,
            [callback, this](MAVLinkParameters::Result result, float value) {
                if (result == MAVLinkParameters::Result::Success) {
                    _parent->call_user_callback(
                        [callback, value]() { callback(Action::Result::Success, value); });
                } else {
                    _parent->call_user_callback(
                        [callback]() { callback(Action::Result::ParameterError, NAN); });
                }
            },
            this);
    } else {
        _parent->call_user_callback(
            [callback, this]() { callback(Action::Result::Success, _takeoff_altitude); });
    }
}

std::pair<Action::Result, float> ActionImpl::get_takeoff_altitude() const
{
    auto prom = std::promise<std::pair<Action::Result, float>>();
    auto fut = prom.get_future();

    get_takeoff_altitude_async([&prom](Action::Result result, float value) {
        prom.set_value(std::pair<Action::Result, float>(result, value));
    });

    return fut.get();
}

void ActionImpl::set_maximum_speed_async(
    const float speed_m_s, const Action::ResultCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // For PX4 we could switch over to the command instead of the param
        // but that would mean that we no longer have the setter functionality.
        _parent->set_param_float_async(
            MAX_SPEED_PARAM,
            speed_m_s,
            [callback, this](MAVLinkParameters::Result result) {
                _parent->call_user_callback([callback, result] {
                    callback(
                        (result == MAVLinkParameters::Result::Success) ?
                            Action::Result::Success :
                            Action::Result::ParameterError);
                });
            },
            this);

    } else {
        MavlinkCommandSender::CommandLong command{};
        command.command = MAV_CMD_DO_CHANGE_SPEED;
        command.target_component_id = _parent->get_autopilot_id();
        command.params.maybe_param1 = 1.0f; // ground speed
        command.params.maybe_param2 = speed_m_s; // ground speed
        command.params.maybe_param3 = -1.0f; // no throttle change
        command.params.maybe_param4 = 0.0f; // absolute

        _parent->send_command_async(
            command, [this, callback](MavlinkCommandSender::Result result, float) {
                command_result_callback(result, callback);
            });
    }
}

Action::Result ActionImpl::set_maximum_speed(float speed_m_s) const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    set_maximum_speed_async(speed_m_s, [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

void ActionImpl::get_maximum_speed_async(const Action::GetMaximumSpeedCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // When using with PX4 we use the param which allows us to have a getter.
        _parent->get_param_float_async(
            MAX_SPEED_PARAM,
            [callback, this](MAVLinkParameters::Result result, float value) {
                if (result == MAVLinkParameters::Result::Success) {
                    _parent->call_user_callback(
                        [callback, value]() { callback(Action::Result::Success, value); });
                } else {
                    _parent->call_user_callback(
                        [callback]() { callback(Action::Result::ParameterError, NAN); });
                }
            },
            this);
    } else {
        _parent->call_user_callback([callback]() { callback(Action::Result::Unsupported, NAN); });
    }
}

std::pair<Action::Result, float> ActionImpl::get_maximum_speed() const
{
    auto prom = std::promise<std::pair<Action::Result, float>>();
    auto fut = prom.get_future();

    get_maximum_speed_async([&prom](Action::Result result, float value) {
        prom.set_value(std::pair<Action::Result, float>(result, value));
    });

    return fut.get();
}

void ActionImpl::set_return_to_launch_altitude_async(
    const float relative_altitude_m, const Action::ResultCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // For PX4 we can access a param.
        _parent->set_param_float_async(
            RTL_RETURN_ALTITUDE_PARAM,
            relative_altitude_m,
            [callback, this](MAVLinkParameters::Result result) {
                _parent->call_user_callback([callback, result] {
                    callback(
                        (result == MAVLinkParameters::Result::Success) ?
                            Action::Result::Success :
                            Action::Result::ParameterError);
                });
            },
            this);

    } else {
        // For ArduPilot this is not clear, and also for Pure mode there is no way
        // that I know of.
        _parent->call_user_callback([callback]() { callback(Action::Result::Unsupported); });
    }
}

Action::Result ActionImpl::set_return_to_launch_altitude(const float relative_altitude_m) const
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    set_return_to_launch_altitude_async(
        relative_altitude_m, [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

void ActionImpl::get_return_to_launch_altitude_async(
    const Action::GetReturnToLaunchAltitudeCallback& callback) const
{
    if (_parent->compatibility_mode() == System::CompatibilityMode::Px4) {
        // When using with PX4 we use the param which allows us to have a getter.
        _parent->get_param_float_async(
            RTL_RETURN_ALTITUDE_PARAM,
            [callback, this](MAVLinkParameters::Result result, float value) {
                if (result == MAVLinkParameters::Result::Success) {
                    _parent->call_user_callback(
                        [callback, value]() { callback(Action::Result::Success, value); });
                } else {
                    _parent->call_user_callback(
                        [callback]() { callback(Action::Result::ParameterError, NAN); });
                }
            },
            this);
    } else {
        _parent->call_user_callback([callback]() { callback(Action::Result::Unsupported, NAN); });
    }
}

std::pair<Action::Result, float> ActionImpl::get_return_to_launch_altitude() const
{
    auto prom = std::promise<std::pair<Action::Result, float>>();
    auto fut = prom.get_future();

    get_return_to_launch_altitude_async([&prom](Action::Result result, float value) {
        prom.set_value(std::pair<Action::Result, float>(result, value));
    });

    return fut.get();
}

void ActionImpl::set_current_speed_async(float speed_m_s, const Action::ResultCallback& callback)
{
    MavlinkCommandSender::CommandLong command{};

    command.command = MAV_CMD_DO_CHANGE_SPEED;
    command.params.maybe_param1 = 1.0f; // ground speed
    command.params.maybe_param2 = speed_m_s;
    command.params.maybe_param3 = -1.0f; // no throttle set
    command.params.maybe_param4 = 0.0f; // reserved
    command.target_component_id = _parent->get_autopilot_id();

    _parent->send_command_async(
        command, [this, callback](MavlinkCommandSender::Result result, float) {
            command_result_callback(result, callback);
        });
}

Action::Result ActionImpl::set_current_speed(float speed_m_s)
{
    auto prom = std::promise<Action::Result>();
    auto fut = prom.get_future();

    set_current_speed_async(speed_m_s, [&prom](Action::Result result) { prom.set_value(result); });

    return fut.get();
}

Action::Result ActionImpl::action_result_from_command_result(MavlinkCommandSender::Result result)
{
    switch (result) {
        case MavlinkCommandSender::Result::Success:
            return Action::Result::Success;
        case MavlinkCommandSender::Result::NoSystem:
            return Action::Result::NoSystem;
        case MavlinkCommandSender::Result::ConnectionError:
            return Action::Result::ConnectionError;
        case MavlinkCommandSender::Result::Busy:
            return Action::Result::Busy;
        case MavlinkCommandSender::Result::Denied:
            // Fallthrough
        case MavlinkCommandSender::Result::TemporarilyRejected:
            return Action::Result::CommandDenied;
        case MavlinkCommandSender::Result::Failed:
            return Action::Result::Failed;
        case MavlinkCommandSender::Result::Timeout:
            return Action::Result::Timeout;
        case MavlinkCommandSender::Result::Unsupported:
            return Action::Result::Unsupported;
        default:
            return Action::Result::Unknown;
    }
}

void ActionImpl::command_result_callback(
    MavlinkCommandSender::Result command_result, const Action::ResultCallback& callback) const
{
    Action::Result action_result = action_result_from_command_result(command_result);

    if (callback) {
        auto temp_callback = callback;
        _parent->call_user_callback(
            [temp_callback, action_result]() { temp_callback(action_result); });
    }
}

} // namespace mavsdk
