// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see
// https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/mission_server/mission_server.proto)

#include <iomanip>

#include "mission_server_impl.h"
#include "plugins/mission_server/mission_server.h"

namespace mavsdk {

using MissionItem = MissionServer::MissionItem;
using MissionPlan = MissionServer::MissionPlan;
using MissionProgress = MissionServer::MissionProgress;

MissionServer::MissionServer(System& system) :
    PluginBase(),
    _impl{std::make_unique<MissionServerImpl>(system)}
{}

MissionServer::MissionServer(std::shared_ptr<System> system) :
    PluginBase(),
    _impl{std::make_unique<MissionServerImpl>(system)}
{}

MissionServer::~MissionServer() {}

void MissionServer::subscribe_incoming_mission(IncomingMissionCallback callback)
{
    _impl->subscribe_incoming_mission(callback);
}

MissionServer::MissionPlan MissionServer::incoming_mission() const
{
    return _impl->incoming_mission();
}

void MissionServer::subscribe_current_item_changed(CurrentItemChangedCallback callback)
{
    _impl->subscribe_current_item_changed(callback);
}

MissionServer::MissionItem MissionServer::current_item_changed() const
{
    return _impl->current_item_changed();
}

void MissionServer::set_current_item_complete_async(const ResultCallback callback)
{
    _impl->set_current_item_complete_async(callback);
}

void MissionServer::set_current_item_complete() const
{
    _impl->set_current_item_complete();
}

void MissionServer::subscribe_clear_all(ClearAllCallback callback)
{
    _impl->subscribe_clear_all(callback);
}

uint32_t MissionServer::clear_all() const
{
    return _impl->clear_all();
}

bool operator==(const MissionServer::MissionItem& lhs, const MissionServer::MissionItem& rhs)
{
    return (rhs.seq == lhs.seq) && (rhs.frame == lhs.frame) && (rhs.command == lhs.command) &&
           (rhs.current == lhs.current) && (rhs.autocontinue == lhs.autocontinue) &&
           ((std::isnan(rhs.param1) && std::isnan(lhs.param1)) || rhs.param1 == lhs.param1) &&
           ((std::isnan(rhs.param2) && std::isnan(lhs.param2)) || rhs.param2 == lhs.param2) &&
           ((std::isnan(rhs.param3) && std::isnan(lhs.param3)) || rhs.param3 == lhs.param3) &&
           ((std::isnan(rhs.param4) && std::isnan(lhs.param4)) || rhs.param4 == lhs.param4) &&
           (rhs.x == lhs.x) && (rhs.y == lhs.y) &&
           ((std::isnan(rhs.z) && std::isnan(lhs.z)) || rhs.z == lhs.z) &&
           (rhs.mission_type == lhs.mission_type);
}

std::ostream& operator<<(std::ostream& str, MissionServer::MissionItem const& mission_item)
{
    str << std::setprecision(15);
    str << "mission_item:" << '\n' << "{\n";
    str << "    seq: " << mission_item.seq << '\n';
    str << "    frame: " << mission_item.frame << '\n';
    str << "    command: " << mission_item.command << '\n';
    str << "    current: " << mission_item.current << '\n';
    str << "    autocontinue: " << mission_item.autocontinue << '\n';
    str << "    param1: " << mission_item.param1 << '\n';
    str << "    param2: " << mission_item.param2 << '\n';
    str << "    param3: " << mission_item.param3 << '\n';
    str << "    param4: " << mission_item.param4 << '\n';
    str << "    x: " << mission_item.x << '\n';
    str << "    y: " << mission_item.y << '\n';
    str << "    z: " << mission_item.z << '\n';
    str << "    mission_type: " << mission_item.mission_type << '\n';
    str << '}';
    return str;
}

bool operator==(const MissionServer::MissionPlan& lhs, const MissionServer::MissionPlan& rhs)
{
    return (rhs.mission_items == lhs.mission_items);
}

std::ostream& operator<<(std::ostream& str, MissionServer::MissionPlan const& mission_plan)
{
    str << std::setprecision(15);
    str << "mission_plan:" << '\n' << "{\n";
    str << "    mission_items: [";
    for (auto it = mission_plan.mission_items.begin(); it != mission_plan.mission_items.end();
         ++it) {
        str << *it;
        str << (it + 1 != mission_plan.mission_items.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(
    const MissionServer::MissionProgress& lhs, const MissionServer::MissionProgress& rhs)
{
    return (rhs.current == lhs.current) && (rhs.total == lhs.total);
}

std::ostream& operator<<(std::ostream& str, MissionServer::MissionProgress const& mission_progress)
{
    str << std::setprecision(15);
    str << "mission_progress:" << '\n' << "{\n";
    str << "    current: " << mission_progress.current << '\n';
    str << "    total: " << mission_progress.total << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, MissionServer::Result const& result)
{
    switch (result) {
        case MissionServer::Result::Unknown:
            return str << "Unknown";
        case MissionServer::Result::Success:
            return str << "Success";
        case MissionServer::Result::Error:
            return str << "Error";
        case MissionServer::Result::TooManyMissionItems:
            return str << "Too Many Mission Items";
        case MissionServer::Result::Busy:
            return str << "Busy";
        case MissionServer::Result::Timeout:
            return str << "Timeout";
        case MissionServer::Result::InvalidArgument:
            return str << "Invalid Argument";
        case MissionServer::Result::Unsupported:
            return str << "Unsupported";
        case MissionServer::Result::NoMissionAvailable:
            return str << "No Mission Available";
        case MissionServer::Result::UnsupportedMissionCmd:
            return str << "Unsupported Mission Cmd";
        case MissionServer::Result::TransferCancelled:
            return str << "Transfer Cancelled";
        case MissionServer::Result::NoSystem:
            return str << "No System";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk