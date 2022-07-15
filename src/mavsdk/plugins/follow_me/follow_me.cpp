// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/follow_me/follow_me.proto)

#include <iomanip>
#include <mutex>

#include "follow_me_impl.h"
#include "plugins/follow_me/follow_me.h"

namespace mavsdk {

using Config = FollowMe::Config;
using TargetLocation = FollowMe::TargetLocation;

FollowMe::FollowMe(System& system) : PluginBase(), _impl{std::make_unique<FollowMeImpl>(system)} {}

FollowMe::FollowMe(std::shared_ptr<System> system) :
    PluginBase(),
    _impl{std::make_unique<FollowMeImpl>(system)}
{}

FollowMe::~FollowMe() {}

FollowMe::Config FollowMe::get_config() const
{
    return _impl->get_config();
}

FollowMe::Result FollowMe::set_config(Config config) const
{
    return _impl->set_config(config);
}

bool FollowMe::is_active() const
{
    return _impl->is_active();
}

FollowMe::Result FollowMe::set_target_location(TargetLocation location) const
{
    return _impl->set_target_location(location);
}

FollowMe::TargetLocation FollowMe::get_last_location() const
{
    return _impl->get_last_location();
}

FollowMe::Result FollowMe::start() const
{
    return _impl->start();
}

FollowMe::Result FollowMe::stop() const
{
    return _impl->stop();
}

std::ostream&
operator<<(std::ostream& str, FollowMe::Config::FollowAltitudeMode const& follow_altitude_mode)
{
    switch (follow_altitude_mode) {
        case FollowMe::Config::FollowAltitudeMode::Constant:
            return str << "Constant";
        case FollowMe::Config::FollowAltitudeMode::Terrain:
            return str << "Terrain";
        case FollowMe::Config::FollowAltitudeMode::TargetGps:
            return str << "Target Gps";
        default:
            return str << "Unknown";
    }
}
bool operator==(const FollowMe::Config& lhs, const FollowMe::Config& rhs)
{
    return ((std::isnan(rhs.follow_height_m) && std::isnan(lhs.follow_height_m)) ||
            rhs.follow_height_m == lhs.follow_height_m) &&
           ((std::isnan(rhs.follow_distance_m) && std::isnan(lhs.follow_distance_m)) ||
            rhs.follow_distance_m == lhs.follow_distance_m) &&
           ((std::isnan(rhs.responsiveness) && std::isnan(lhs.responsiveness)) ||
            rhs.responsiveness == lhs.responsiveness) &&
           (rhs.altitude_mode == lhs.altitude_mode) &&
           ((std::isnan(rhs.max_tangential_vel_m_s) && std::isnan(lhs.max_tangential_vel_m_s)) ||
            rhs.max_tangential_vel_m_s == lhs.max_tangential_vel_m_s) &&
           ((std::isnan(rhs.follow_angle_deg) && std::isnan(lhs.follow_angle_deg)) ||
            rhs.follow_angle_deg == lhs.follow_angle_deg);
}

std::ostream& operator<<(std::ostream& str, FollowMe::Config const& config)
{
    str << std::setprecision(15);
    str << "config:" << '\n' << "{\n";
    str << "    follow_height_m: " << config.follow_height_m << '\n';
    str << "    follow_distance_m: " << config.follow_distance_m << '\n';
    str << "    responsiveness: " << config.responsiveness << '\n';
    str << "    altitude_mode: " << config.altitude_mode << '\n';
    str << "    max_tangential_vel_m_s: " << config.max_tangential_vel_m_s << '\n';
    str << "    follow_angle_deg: " << config.follow_angle_deg << '\n';
    str << '}';
    return str;
}

bool operator==(const FollowMe::TargetLocation& lhs, const FollowMe::TargetLocation& rhs)
{
    return ((std::isnan(rhs.latitude_deg) && std::isnan(lhs.latitude_deg)) ||
            rhs.latitude_deg == lhs.latitude_deg) &&
           ((std::isnan(rhs.longitude_deg) && std::isnan(lhs.longitude_deg)) ||
            rhs.longitude_deg == lhs.longitude_deg) &&
           ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) ||
            rhs.absolute_altitude_m == lhs.absolute_altitude_m) &&
           ((std::isnan(rhs.velocity_x_m_s) && std::isnan(lhs.velocity_x_m_s)) ||
            rhs.velocity_x_m_s == lhs.velocity_x_m_s) &&
           ((std::isnan(rhs.velocity_y_m_s) && std::isnan(lhs.velocity_y_m_s)) ||
            rhs.velocity_y_m_s == lhs.velocity_y_m_s) &&
           ((std::isnan(rhs.velocity_z_m_s) && std::isnan(lhs.velocity_z_m_s)) ||
            rhs.velocity_z_m_s == lhs.velocity_z_m_s);
}

std::ostream& operator<<(std::ostream& str, FollowMe::TargetLocation const& target_location)
{
    str << std::setprecision(15);
    str << "target_location:" << '\n' << "{\n";
    str << "    latitude_deg: " << target_location.latitude_deg << '\n';
    str << "    longitude_deg: " << target_location.longitude_deg << '\n';
    str << "    absolute_altitude_m: " << target_location.absolute_altitude_m << '\n';
    str << "    velocity_x_m_s: " << target_location.velocity_x_m_s << '\n';
    str << "    velocity_y_m_s: " << target_location.velocity_y_m_s << '\n';
    str << "    velocity_z_m_s: " << target_location.velocity_z_m_s << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, FollowMe::Result const& result)
{
    switch (result) {
        case FollowMe::Result::Unknown:
            return str << "Unknown";
        case FollowMe::Result::Success:
            return str << "Success";
        case FollowMe::Result::NoSystem:
            return str << "No System";
        case FollowMe::Result::ConnectionError:
            return str << "Connection Error";
        case FollowMe::Result::Busy:
            return str << "Busy";
        case FollowMe::Result::CommandDenied:
            return str << "Command Denied";
        case FollowMe::Result::Timeout:
            return str << "Timeout";
        case FollowMe::Result::NotActive:
            return str << "Not Active";
        case FollowMe::Result::SetConfigFailed:
            return str << "Set Config Failed";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk