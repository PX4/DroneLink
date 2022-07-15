// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/offboard/offboard.proto)

#include <iomanip>
#include <mutex>

#include "offboard_impl.h"
#include "plugins/offboard/offboard.h"

namespace mavsdk {

using Attitude = Offboard::Attitude;
using ActuatorControlGroup = Offboard::ActuatorControlGroup;
using ActuatorControl = Offboard::ActuatorControl;
using AttitudeRate = Offboard::AttitudeRate;
using PositionNedYaw = Offboard::PositionNedYaw;
using PositionGlobalYaw = Offboard::PositionGlobalYaw;
using VelocityBodyYawspeed = Offboard::VelocityBodyYawspeed;
using VelocityNedYaw = Offboard::VelocityNedYaw;
using AccelerationNed = Offboard::AccelerationNed;

Offboard::Offboard(System& system) : PluginBase(), _impl{std::make_unique<OffboardImpl>(system)} {}

Offboard::Offboard(std::shared_ptr<System> system) :
    PluginBase(),
    _impl{std::make_unique<OffboardImpl>(system)}
{}

Offboard::~Offboard() {}

void Offboard::start_async(const ResultCallback callback)
{
    _impl->start_async(callback);
}

Offboard::Result Offboard::start() const
{
    return _impl->start();
}

void Offboard::stop_async(const ResultCallback callback)
{
    _impl->stop_async(callback);
}

Offboard::Result Offboard::stop() const
{
    return _impl->stop();
}

bool Offboard::is_active() const
{
    return _impl->is_active();
}

Offboard::Result Offboard::set_attitude(Attitude attitude) const
{
    return _impl->set_attitude(attitude);
}

Offboard::Result Offboard::set_actuator_control(ActuatorControl actuator_control) const
{
    return _impl->set_actuator_control(actuator_control);
}

Offboard::Result Offboard::set_attitude_rate(AttitudeRate attitude_rate) const
{
    return _impl->set_attitude_rate(attitude_rate);
}

Offboard::Result Offboard::set_position_ned(PositionNedYaw position_ned_yaw) const
{
    return _impl->set_position_ned(position_ned_yaw);
}

Offboard::Result Offboard::set_position_global(PositionGlobalYaw position_global_yaw) const
{
    return _impl->set_position_global(position_global_yaw);
}

Offboard::Result Offboard::set_velocity_body(VelocityBodyYawspeed velocity_body_yawspeed) const
{
    return _impl->set_velocity_body(velocity_body_yawspeed);
}

Offboard::Result Offboard::set_velocity_ned(VelocityNedYaw velocity_ned_yaw) const
{
    return _impl->set_velocity_ned(velocity_ned_yaw);
}

Offboard::Result Offboard::set_position_velocity_ned(
    PositionNedYaw position_ned_yaw, VelocityNedYaw velocity_ned_yaw) const
{
    return _impl->set_position_velocity_ned(position_ned_yaw, velocity_ned_yaw);
}

Offboard::Result Offboard::set_acceleration_ned(AccelerationNed acceleration_ned) const
{
    return _impl->set_acceleration_ned(acceleration_ned);
}

bool operator==(const Offboard::Attitude& lhs, const Offboard::Attitude& rhs)
{
    return ((std::isnan(rhs.roll_deg) && std::isnan(lhs.roll_deg)) ||
            rhs.roll_deg == lhs.roll_deg) &&
           ((std::isnan(rhs.pitch_deg) && std::isnan(lhs.pitch_deg)) ||
            rhs.pitch_deg == lhs.pitch_deg) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg) &&
           ((std::isnan(rhs.thrust_value) && std::isnan(lhs.thrust_value)) ||
            rhs.thrust_value == lhs.thrust_value);
}

std::ostream& operator<<(std::ostream& str, Offboard::Attitude const& attitude)
{
    str << std::setprecision(15);
    str << "attitude:" << '\n' << "{\n";
    str << "    roll_deg: " << attitude.roll_deg << '\n';
    str << "    pitch_deg: " << attitude.pitch_deg << '\n';
    str << "    yaw_deg: " << attitude.yaw_deg << '\n';
    str << "    thrust_value: " << attitude.thrust_value << '\n';
    str << '}';
    return str;
}

bool operator==(
    const Offboard::ActuatorControlGroup& lhs, const Offboard::ActuatorControlGroup& rhs)
{
    return (rhs.controls == lhs.controls);
}

std::ostream&
operator<<(std::ostream& str, Offboard::ActuatorControlGroup const& actuator_control_group)
{
    str << std::setprecision(15);
    str << "actuator_control_group:" << '\n' << "{\n";
    str << "    controls: [";
    for (auto it = actuator_control_group.controls.begin();
         it != actuator_control_group.controls.end();
         ++it) {
        str << *it;
        str << (it + 1 != actuator_control_group.controls.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(const Offboard::ActuatorControl& lhs, const Offboard::ActuatorControl& rhs)
{
    return (rhs.groups == lhs.groups);
}

std::ostream& operator<<(std::ostream& str, Offboard::ActuatorControl const& actuator_control)
{
    str << std::setprecision(15);
    str << "actuator_control:" << '\n' << "{\n";
    str << "    groups: [";
    for (auto it = actuator_control.groups.begin(); it != actuator_control.groups.end(); ++it) {
        str << *it;
        str << (it + 1 != actuator_control.groups.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(const Offboard::AttitudeRate& lhs, const Offboard::AttitudeRate& rhs)
{
    return ((std::isnan(rhs.roll_deg_s) && std::isnan(lhs.roll_deg_s)) ||
            rhs.roll_deg_s == lhs.roll_deg_s) &&
           ((std::isnan(rhs.pitch_deg_s) && std::isnan(lhs.pitch_deg_s)) ||
            rhs.pitch_deg_s == lhs.pitch_deg_s) &&
           ((std::isnan(rhs.yaw_deg_s) && std::isnan(lhs.yaw_deg_s)) ||
            rhs.yaw_deg_s == lhs.yaw_deg_s) &&
           ((std::isnan(rhs.thrust_value) && std::isnan(lhs.thrust_value)) ||
            rhs.thrust_value == lhs.thrust_value);
}

std::ostream& operator<<(std::ostream& str, Offboard::AttitudeRate const& attitude_rate)
{
    str << std::setprecision(15);
    str << "attitude_rate:" << '\n' << "{\n";
    str << "    roll_deg_s: " << attitude_rate.roll_deg_s << '\n';
    str << "    pitch_deg_s: " << attitude_rate.pitch_deg_s << '\n';
    str << "    yaw_deg_s: " << attitude_rate.yaw_deg_s << '\n';
    str << "    thrust_value: " << attitude_rate.thrust_value << '\n';
    str << '}';
    return str;
}

bool operator==(const Offboard::PositionNedYaw& lhs, const Offboard::PositionNedYaw& rhs)
{
    return ((std::isnan(rhs.north_m) && std::isnan(lhs.north_m)) || rhs.north_m == lhs.north_m) &&
           ((std::isnan(rhs.east_m) && std::isnan(lhs.east_m)) || rhs.east_m == lhs.east_m) &&
           ((std::isnan(rhs.down_m) && std::isnan(lhs.down_m)) || rhs.down_m == lhs.down_m) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg);
}

std::ostream& operator<<(std::ostream& str, Offboard::PositionNedYaw const& position_ned_yaw)
{
    str << std::setprecision(15);
    str << "position_ned_yaw:" << '\n' << "{\n";
    str << "    north_m: " << position_ned_yaw.north_m << '\n';
    str << "    east_m: " << position_ned_yaw.east_m << '\n';
    str << "    down_m: " << position_ned_yaw.down_m << '\n';
    str << "    yaw_deg: " << position_ned_yaw.yaw_deg << '\n';
    str << '}';
    return str;
}

std::ostream&
operator<<(std::ostream& str, Offboard::PositionGlobalYaw::AltitudeType const& altitude_type)
{
    switch (altitude_type) {
        case Offboard::PositionGlobalYaw::AltitudeType::RelHome:
            return str << "Rel Home";
        case Offboard::PositionGlobalYaw::AltitudeType::Amsl:
            return str << "Amsl";
        case Offboard::PositionGlobalYaw::AltitudeType::Agl:
            return str << "Agl";
        default:
            return str << "Unknown";
    }
}
bool operator==(const Offboard::PositionGlobalYaw& lhs, const Offboard::PositionGlobalYaw& rhs)
{
    return ((std::isnan(rhs.lat_deg) && std::isnan(lhs.lat_deg)) || rhs.lat_deg == lhs.lat_deg) &&
           ((std::isnan(rhs.lon_deg) && std::isnan(lhs.lon_deg)) || rhs.lon_deg == lhs.lon_deg) &&
           ((std::isnan(rhs.alt_m) && std::isnan(lhs.alt_m)) || rhs.alt_m == lhs.alt_m) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg) &&
           (rhs.altitude_type == lhs.altitude_type);
}

std::ostream& operator<<(std::ostream& str, Offboard::PositionGlobalYaw const& position_global_yaw)
{
    str << std::setprecision(15);
    str << "position_global_yaw:" << '\n' << "{\n";
    str << "    lat_deg: " << position_global_yaw.lat_deg << '\n';
    str << "    lon_deg: " << position_global_yaw.lon_deg << '\n';
    str << "    alt_m: " << position_global_yaw.alt_m << '\n';
    str << "    yaw_deg: " << position_global_yaw.yaw_deg << '\n';
    str << "    altitude_type: " << position_global_yaw.altitude_type << '\n';
    str << '}';
    return str;
}

bool operator==(
    const Offboard::VelocityBodyYawspeed& lhs, const Offboard::VelocityBodyYawspeed& rhs)
{
    return ((std::isnan(rhs.forward_m_s) && std::isnan(lhs.forward_m_s)) ||
            rhs.forward_m_s == lhs.forward_m_s) &&
           ((std::isnan(rhs.right_m_s) && std::isnan(lhs.right_m_s)) ||
            rhs.right_m_s == lhs.right_m_s) &&
           ((std::isnan(rhs.down_m_s) && std::isnan(lhs.down_m_s)) ||
            rhs.down_m_s == lhs.down_m_s) &&
           ((std::isnan(rhs.yawspeed_deg_s) && std::isnan(lhs.yawspeed_deg_s)) ||
            rhs.yawspeed_deg_s == lhs.yawspeed_deg_s);
}

std::ostream&
operator<<(std::ostream& str, Offboard::VelocityBodyYawspeed const& velocity_body_yawspeed)
{
    str << std::setprecision(15);
    str << "velocity_body_yawspeed:" << '\n' << "{\n";
    str << "    forward_m_s: " << velocity_body_yawspeed.forward_m_s << '\n';
    str << "    right_m_s: " << velocity_body_yawspeed.right_m_s << '\n';
    str << "    down_m_s: " << velocity_body_yawspeed.down_m_s << '\n';
    str << "    yawspeed_deg_s: " << velocity_body_yawspeed.yawspeed_deg_s << '\n';
    str << '}';
    return str;
}

bool operator==(const Offboard::VelocityNedYaw& lhs, const Offboard::VelocityNedYaw& rhs)
{
    return ((std::isnan(rhs.north_m_s) && std::isnan(lhs.north_m_s)) ||
            rhs.north_m_s == lhs.north_m_s) &&
           ((std::isnan(rhs.east_m_s) && std::isnan(lhs.east_m_s)) ||
            rhs.east_m_s == lhs.east_m_s) &&
           ((std::isnan(rhs.down_m_s) && std::isnan(lhs.down_m_s)) ||
            rhs.down_m_s == lhs.down_m_s) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg);
}

std::ostream& operator<<(std::ostream& str, Offboard::VelocityNedYaw const& velocity_ned_yaw)
{
    str << std::setprecision(15);
    str << "velocity_ned_yaw:" << '\n' << "{\n";
    str << "    north_m_s: " << velocity_ned_yaw.north_m_s << '\n';
    str << "    east_m_s: " << velocity_ned_yaw.east_m_s << '\n';
    str << "    down_m_s: " << velocity_ned_yaw.down_m_s << '\n';
    str << "    yaw_deg: " << velocity_ned_yaw.yaw_deg << '\n';
    str << '}';
    return str;
}

bool operator==(const Offboard::AccelerationNed& lhs, const Offboard::AccelerationNed& rhs)
{
    return ((std::isnan(rhs.north_m_s2) && std::isnan(lhs.north_m_s2)) ||
            rhs.north_m_s2 == lhs.north_m_s2) &&
           ((std::isnan(rhs.east_m_s2) && std::isnan(lhs.east_m_s2)) ||
            rhs.east_m_s2 == lhs.east_m_s2) &&
           ((std::isnan(rhs.down_m_s2) && std::isnan(lhs.down_m_s2)) ||
            rhs.down_m_s2 == lhs.down_m_s2);
}

std::ostream& operator<<(std::ostream& str, Offboard::AccelerationNed const& acceleration_ned)
{
    str << std::setprecision(15);
    str << "acceleration_ned:" << '\n' << "{\n";
    str << "    north_m_s2: " << acceleration_ned.north_m_s2 << '\n';
    str << "    east_m_s2: " << acceleration_ned.east_m_s2 << '\n';
    str << "    down_m_s2: " << acceleration_ned.down_m_s2 << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, Offboard::Result const& result)
{
    switch (result) {
        case Offboard::Result::Unknown:
            return str << "Unknown";
        case Offboard::Result::Success:
            return str << "Success";
        case Offboard::Result::NoSystem:
            return str << "No System";
        case Offboard::Result::ConnectionError:
            return str << "Connection Error";
        case Offboard::Result::Busy:
            return str << "Busy";
        case Offboard::Result::CommandDenied:
            return str << "Command Denied";
        case Offboard::Result::Timeout:
            return str << "Timeout";
        case Offboard::Result::NoSetpointSet:
            return str << "No Setpoint Set";
        case Offboard::Result::Failed:
            return str << "Failed";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk