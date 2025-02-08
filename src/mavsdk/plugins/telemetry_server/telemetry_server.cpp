// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see
// https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/telemetry_server/telemetry_server.proto)

#include <iomanip>

#include "telemetry_server_impl.h"
#include "plugins/telemetry_server/telemetry_server.h"

namespace mavsdk {

using Position = TelemetryServer::Position;
using Heading = TelemetryServer::Heading;
using Quaternion = TelemetryServer::Quaternion;
using EulerAngle = TelemetryServer::EulerAngle;
using AngularVelocityBody = TelemetryServer::AngularVelocityBody;
using GpsInfo = TelemetryServer::GpsInfo;
using RawGps = TelemetryServer::RawGps;
using Battery = TelemetryServer::Battery;
using RcStatus = TelemetryServer::RcStatus;
using StatusText = TelemetryServer::StatusText;
using ActuatorControlTarget = TelemetryServer::ActuatorControlTarget;
using ActuatorOutputStatus = TelemetryServer::ActuatorOutputStatus;
using Covariance = TelemetryServer::Covariance;
using VelocityBody = TelemetryServer::VelocityBody;
using PositionBody = TelemetryServer::PositionBody;
using Odometry = TelemetryServer::Odometry;
using DistanceSensor = TelemetryServer::DistanceSensor;
using ScaledPressure = TelemetryServer::ScaledPressure;
using PositionNed = TelemetryServer::PositionNed;
using VelocityNed = TelemetryServer::VelocityNed;
using PositionVelocityNed = TelemetryServer::PositionVelocityNed;
using GroundTruth = TelemetryServer::GroundTruth;
using FixedwingMetrics = TelemetryServer::FixedwingMetrics;
using AccelerationFrd = TelemetryServer::AccelerationFrd;
using AngularVelocityFrd = TelemetryServer::AngularVelocityFrd;
using MagneticFieldFrd = TelemetryServer::MagneticFieldFrd;
using Imu = TelemetryServer::Imu;

TelemetryServer::TelemetryServer(std::shared_ptr<ServerComponent> server_component) :
    ServerPluginBase(),
    _impl{std::make_unique<TelemetryServerImpl>(server_component)}
{}

TelemetryServer::~TelemetryServer() {}

TelemetryServer::Result TelemetryServer::publish_position(
    Position position, VelocityNed velocity_ned, Heading heading) const
{
    return _impl->publish_position(position, velocity_ned, heading);
}

TelemetryServer::Result TelemetryServer::publish_home(Position home) const
{
    return _impl->publish_home(home);
}

TelemetryServer::Result TelemetryServer::publish_sys_status(
    Battery battery,
    bool rc_receiver_status,
    bool gyro_status,
    bool accel_status,
    bool mag_status,
    bool gps_status) const
{
    return _impl->publish_sys_status(
        battery, rc_receiver_status, gyro_status, accel_status, mag_status, gps_status);
}

TelemetryServer::Result
TelemetryServer::publish_extended_sys_state(VtolState vtol_state, LandedState landed_state) const
{
    return _impl->publish_extended_sys_state(vtol_state, landed_state);
}

TelemetryServer::Result TelemetryServer::publish_raw_gps(RawGps raw_gps, GpsInfo gps_info) const
{
    return _impl->publish_raw_gps(raw_gps, gps_info);
}

TelemetryServer::Result TelemetryServer::publish_battery(Battery battery) const
{
    return _impl->publish_battery(battery);
}

TelemetryServer::Result TelemetryServer::publish_status_text(StatusText status_text) const
{
    return _impl->publish_status_text(status_text);
}

TelemetryServer::Result TelemetryServer::publish_odometry(Odometry odometry) const
{
    return _impl->publish_odometry(odometry);
}

TelemetryServer::Result
TelemetryServer::publish_position_velocity_ned(PositionVelocityNed position_velocity_ned) const
{
    return _impl->publish_position_velocity_ned(position_velocity_ned);
}

TelemetryServer::Result TelemetryServer::publish_ground_truth(GroundTruth ground_truth) const
{
    return _impl->publish_ground_truth(ground_truth);
}

TelemetryServer::Result TelemetryServer::publish_imu(Imu imu) const
{
    return _impl->publish_imu(imu);
}

TelemetryServer::Result TelemetryServer::publish_scaled_imu(Imu imu) const
{
    return _impl->publish_scaled_imu(imu);
}

TelemetryServer::Result TelemetryServer::publish_raw_imu(Imu imu) const
{
    return _impl->publish_raw_imu(imu);
}

TelemetryServer::Result TelemetryServer::publish_unix_epoch_time(uint64_t time_us) const
{
    return _impl->publish_unix_epoch_time(time_us);
}

TelemetryServer::Result
TelemetryServer::publish_distance_sensor(DistanceSensor distance_sensor) const
{
    return _impl->publish_distance_sensor(distance_sensor);
}

TelemetryServer::Result
TelemetryServer::publish_attitude(EulerAngle angle, AngularVelocityBody angular_velocity) const
{
    return _impl->publish_attitude(angle, angular_velocity);
}

TelemetryServer::Result
TelemetryServer::publish_visual_flight_rules_hud(FixedwingMetrics fixed_wing_metrics) const
{
    return _impl->publish_visual_flight_rules_hud(fixed_wing_metrics);
}

bool operator==(const TelemetryServer::Position& lhs, const TelemetryServer::Position& rhs)
{
    return ((std::isnan(rhs.latitude_deg) && std::isnan(lhs.latitude_deg)) ||
            rhs.latitude_deg == lhs.latitude_deg) &&
           ((std::isnan(rhs.longitude_deg) && std::isnan(lhs.longitude_deg)) ||
            rhs.longitude_deg == lhs.longitude_deg) &&
           ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) ||
            rhs.absolute_altitude_m == lhs.absolute_altitude_m) &&
           ((std::isnan(rhs.relative_altitude_m) && std::isnan(lhs.relative_altitude_m)) ||
            rhs.relative_altitude_m == lhs.relative_altitude_m);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Position const& position)
{
    str << std::setprecision(15);
    str << "position:" << '\n' << "{\n";
    str << "    latitude_deg: " << position.latitude_deg << '\n';
    str << "    longitude_deg: " << position.longitude_deg << '\n';
    str << "    absolute_altitude_m: " << position.absolute_altitude_m << '\n';
    str << "    relative_altitude_m: " << position.relative_altitude_m << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::Heading& lhs, const TelemetryServer::Heading& rhs)
{
    return (
        (std::isnan(rhs.heading_deg) && std::isnan(lhs.heading_deg)) ||
        rhs.heading_deg == lhs.heading_deg);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Heading const& heading)
{
    str << std::setprecision(15);
    str << "heading:" << '\n' << "{\n";
    str << "    heading_deg: " << heading.heading_deg << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::Quaternion& lhs, const TelemetryServer::Quaternion& rhs)
{
    return ((std::isnan(rhs.w) && std::isnan(lhs.w)) || rhs.w == lhs.w) &&
           ((std::isnan(rhs.x) && std::isnan(lhs.x)) || rhs.x == lhs.x) &&
           ((std::isnan(rhs.y) && std::isnan(lhs.y)) || rhs.y == lhs.y) &&
           ((std::isnan(rhs.z) && std::isnan(lhs.z)) || rhs.z == lhs.z) &&
           (rhs.timestamp_us == lhs.timestamp_us);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Quaternion const& quaternion)
{
    str << std::setprecision(15);
    str << "quaternion:" << '\n' << "{\n";
    str << "    w: " << quaternion.w << '\n';
    str << "    x: " << quaternion.x << '\n';
    str << "    y: " << quaternion.y << '\n';
    str << "    z: " << quaternion.z << '\n';
    str << "    timestamp_us: " << quaternion.timestamp_us << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::EulerAngle& lhs, const TelemetryServer::EulerAngle& rhs)
{
    return ((std::isnan(rhs.roll_deg) && std::isnan(lhs.roll_deg)) ||
            rhs.roll_deg == lhs.roll_deg) &&
           ((std::isnan(rhs.pitch_deg) && std::isnan(lhs.pitch_deg)) ||
            rhs.pitch_deg == lhs.pitch_deg) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg) &&
           (rhs.timestamp_us == lhs.timestamp_us);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::EulerAngle const& euler_angle)
{
    str << std::setprecision(15);
    str << "euler_angle:" << '\n' << "{\n";
    str << "    roll_deg: " << euler_angle.roll_deg << '\n';
    str << "    pitch_deg: " << euler_angle.pitch_deg << '\n';
    str << "    yaw_deg: " << euler_angle.yaw_deg << '\n';
    str << "    timestamp_us: " << euler_angle.timestamp_us << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::AngularVelocityBody& lhs,
    const TelemetryServer::AngularVelocityBody& rhs)
{
    return ((std::isnan(rhs.roll_rad_s) && std::isnan(lhs.roll_rad_s)) ||
            rhs.roll_rad_s == lhs.roll_rad_s) &&
           ((std::isnan(rhs.pitch_rad_s) && std::isnan(lhs.pitch_rad_s)) ||
            rhs.pitch_rad_s == lhs.pitch_rad_s) &&
           ((std::isnan(rhs.yaw_rad_s) && std::isnan(lhs.yaw_rad_s)) ||
            rhs.yaw_rad_s == lhs.yaw_rad_s);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::AngularVelocityBody const& angular_velocity_body)
{
    str << std::setprecision(15);
    str << "angular_velocity_body:" << '\n' << "{\n";
    str << "    roll_rad_s: " << angular_velocity_body.roll_rad_s << '\n';
    str << "    pitch_rad_s: " << angular_velocity_body.pitch_rad_s << '\n';
    str << "    yaw_rad_s: " << angular_velocity_body.yaw_rad_s << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::GpsInfo& lhs, const TelemetryServer::GpsInfo& rhs)
{
    return (rhs.num_satellites == lhs.num_satellites) && (rhs.fix_type == lhs.fix_type);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::GpsInfo const& gps_info)
{
    str << std::setprecision(15);
    str << "gps_info:" << '\n' << "{\n";
    str << "    num_satellites: " << gps_info.num_satellites << '\n';
    str << "    fix_type: " << gps_info.fix_type << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::RawGps& lhs, const TelemetryServer::RawGps& rhs)
{
    return (rhs.timestamp_us == lhs.timestamp_us) &&
           ((std::isnan(rhs.latitude_deg) && std::isnan(lhs.latitude_deg)) ||
            rhs.latitude_deg == lhs.latitude_deg) &&
           ((std::isnan(rhs.longitude_deg) && std::isnan(lhs.longitude_deg)) ||
            rhs.longitude_deg == lhs.longitude_deg) &&
           ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) ||
            rhs.absolute_altitude_m == lhs.absolute_altitude_m) &&
           ((std::isnan(rhs.hdop) && std::isnan(lhs.hdop)) || rhs.hdop == lhs.hdop) &&
           ((std::isnan(rhs.vdop) && std::isnan(lhs.vdop)) || rhs.vdop == lhs.vdop) &&
           ((std::isnan(rhs.velocity_m_s) && std::isnan(lhs.velocity_m_s)) ||
            rhs.velocity_m_s == lhs.velocity_m_s) &&
           ((std::isnan(rhs.cog_deg) && std::isnan(lhs.cog_deg)) || rhs.cog_deg == lhs.cog_deg) &&
           ((std::isnan(rhs.altitude_ellipsoid_m) && std::isnan(lhs.altitude_ellipsoid_m)) ||
            rhs.altitude_ellipsoid_m == lhs.altitude_ellipsoid_m) &&
           ((std::isnan(rhs.horizontal_uncertainty_m) &&
             std::isnan(lhs.horizontal_uncertainty_m)) ||
            rhs.horizontal_uncertainty_m == lhs.horizontal_uncertainty_m) &&
           ((std::isnan(rhs.vertical_uncertainty_m) && std::isnan(lhs.vertical_uncertainty_m)) ||
            rhs.vertical_uncertainty_m == lhs.vertical_uncertainty_m) &&
           ((std::isnan(rhs.velocity_uncertainty_m_s) &&
             std::isnan(lhs.velocity_uncertainty_m_s)) ||
            rhs.velocity_uncertainty_m_s == lhs.velocity_uncertainty_m_s) &&
           ((std::isnan(rhs.heading_uncertainty_deg) && std::isnan(lhs.heading_uncertainty_deg)) ||
            rhs.heading_uncertainty_deg == lhs.heading_uncertainty_deg) &&
           ((std::isnan(rhs.yaw_deg) && std::isnan(lhs.yaw_deg)) || rhs.yaw_deg == lhs.yaw_deg);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::RawGps const& raw_gps)
{
    str << std::setprecision(15);
    str << "raw_gps:" << '\n' << "{\n";
    str << "    timestamp_us: " << raw_gps.timestamp_us << '\n';
    str << "    latitude_deg: " << raw_gps.latitude_deg << '\n';
    str << "    longitude_deg: " << raw_gps.longitude_deg << '\n';
    str << "    absolute_altitude_m: " << raw_gps.absolute_altitude_m << '\n';
    str << "    hdop: " << raw_gps.hdop << '\n';
    str << "    vdop: " << raw_gps.vdop << '\n';
    str << "    velocity_m_s: " << raw_gps.velocity_m_s << '\n';
    str << "    cog_deg: " << raw_gps.cog_deg << '\n';
    str << "    altitude_ellipsoid_m: " << raw_gps.altitude_ellipsoid_m << '\n';
    str << "    horizontal_uncertainty_m: " << raw_gps.horizontal_uncertainty_m << '\n';
    str << "    vertical_uncertainty_m: " << raw_gps.vertical_uncertainty_m << '\n';
    str << "    velocity_uncertainty_m_s: " << raw_gps.velocity_uncertainty_m_s << '\n';
    str << "    heading_uncertainty_deg: " << raw_gps.heading_uncertainty_deg << '\n';
    str << "    yaw_deg: " << raw_gps.yaw_deg << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::Battery& lhs, const TelemetryServer::Battery& rhs)
{
    return ((std::isnan(rhs.voltage_v) && std::isnan(lhs.voltage_v)) ||
            rhs.voltage_v == lhs.voltage_v) &&
           ((std::isnan(rhs.remaining_percent) && std::isnan(lhs.remaining_percent)) ||
            rhs.remaining_percent == lhs.remaining_percent);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Battery const& battery)
{
    str << std::setprecision(15);
    str << "battery:" << '\n' << "{\n";
    str << "    voltage_v: " << battery.voltage_v << '\n';
    str << "    remaining_percent: " << battery.remaining_percent << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::RcStatus& lhs, const TelemetryServer::RcStatus& rhs)
{
    return (rhs.was_available_once == lhs.was_available_once) &&
           (rhs.is_available == lhs.is_available) &&
           ((std::isnan(rhs.signal_strength_percent) && std::isnan(lhs.signal_strength_percent)) ||
            rhs.signal_strength_percent == lhs.signal_strength_percent);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::RcStatus const& rc_status)
{
    str << std::setprecision(15);
    str << "rc_status:" << '\n' << "{\n";
    str << "    was_available_once: " << rc_status.was_available_once << '\n';
    str << "    is_available: " << rc_status.is_available << '\n';
    str << "    signal_strength_percent: " << rc_status.signal_strength_percent << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::StatusText& lhs, const TelemetryServer::StatusText& rhs)
{
    return (rhs.type == lhs.type) && (rhs.text == lhs.text);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::StatusText const& status_text)
{
    str << std::setprecision(15);
    str << "status_text:" << '\n' << "{\n";
    str << "    type: " << status_text.type << '\n';
    str << "    text: " << status_text.text << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::ActuatorControlTarget& lhs,
    const TelemetryServer::ActuatorControlTarget& rhs)
{
    return (rhs.group == lhs.group) && (rhs.controls == lhs.controls);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::ActuatorControlTarget const& actuator_control_target)
{
    str << std::setprecision(15);
    str << "actuator_control_target:" << '\n' << "{\n";
    str << "    group: " << actuator_control_target.group << '\n';
    str << "    controls: [";
    for (auto it = actuator_control_target.controls.begin();
         it != actuator_control_target.controls.end();
         ++it) {
        str << *it;
        str << (it + 1 != actuator_control_target.controls.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::ActuatorOutputStatus& lhs,
    const TelemetryServer::ActuatorOutputStatus& rhs)
{
    return (rhs.active == lhs.active) && (rhs.actuator == lhs.actuator);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::ActuatorOutputStatus const& actuator_output_status)
{
    str << std::setprecision(15);
    str << "actuator_output_status:" << '\n' << "{\n";
    str << "    active: " << actuator_output_status.active << '\n';
    str << "    actuator: [";
    for (auto it = actuator_output_status.actuator.begin();
         it != actuator_output_status.actuator.end();
         ++it) {
        str << *it;
        str << (it + 1 != actuator_output_status.actuator.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::Covariance& lhs, const TelemetryServer::Covariance& rhs)
{
    return (rhs.covariance_matrix == lhs.covariance_matrix);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Covariance const& covariance)
{
    str << std::setprecision(15);
    str << "covariance:" << '\n' << "{\n";
    str << "    covariance_matrix: [";
    for (auto it = covariance.covariance_matrix.begin(); it != covariance.covariance_matrix.end();
         ++it) {
        str << *it;
        str << (it + 1 != covariance.covariance_matrix.end() ? ", " : "]\n");
    }
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::VelocityBody& lhs, const TelemetryServer::VelocityBody& rhs)
{
    return ((std::isnan(rhs.x_m_s) && std::isnan(lhs.x_m_s)) || rhs.x_m_s == lhs.x_m_s) &&
           ((std::isnan(rhs.y_m_s) && std::isnan(lhs.y_m_s)) || rhs.y_m_s == lhs.y_m_s) &&
           ((std::isnan(rhs.z_m_s) && std::isnan(lhs.z_m_s)) || rhs.z_m_s == lhs.z_m_s);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::VelocityBody const& velocity_body)
{
    str << std::setprecision(15);
    str << "velocity_body:" << '\n' << "{\n";
    str << "    x_m_s: " << velocity_body.x_m_s << '\n';
    str << "    y_m_s: " << velocity_body.y_m_s << '\n';
    str << "    z_m_s: " << velocity_body.z_m_s << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::PositionBody& lhs, const TelemetryServer::PositionBody& rhs)
{
    return ((std::isnan(rhs.x_m) && std::isnan(lhs.x_m)) || rhs.x_m == lhs.x_m) &&
           ((std::isnan(rhs.y_m) && std::isnan(lhs.y_m)) || rhs.y_m == lhs.y_m) &&
           ((std::isnan(rhs.z_m) && std::isnan(lhs.z_m)) || rhs.z_m == lhs.z_m);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::PositionBody const& position_body)
{
    str << std::setprecision(15);
    str << "position_body:" << '\n' << "{\n";
    str << "    x_m: " << position_body.x_m << '\n';
    str << "    y_m: " << position_body.y_m << '\n';
    str << "    z_m: " << position_body.z_m << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Odometry::MavFrame const& mav_frame)
{
    switch (mav_frame) {
        case TelemetryServer::Odometry::MavFrame::Undef:
            return str << "Undef";
        case TelemetryServer::Odometry::MavFrame::BodyNed:
            return str << "Body Ned";
        case TelemetryServer::Odometry::MavFrame::VisionNed:
            return str << "Vision Ned";
        case TelemetryServer::Odometry::MavFrame::EstimNed:
            return str << "Estim Ned";
        default:
            return str << "Unknown";
    }
}
bool operator==(const TelemetryServer::Odometry& lhs, const TelemetryServer::Odometry& rhs)
{
    return (rhs.time_usec == lhs.time_usec) && (rhs.frame_id == lhs.frame_id) &&
           (rhs.child_frame_id == lhs.child_frame_id) && (rhs.position_body == lhs.position_body) &&
           (rhs.q == lhs.q) && (rhs.velocity_body == lhs.velocity_body) &&
           (rhs.angular_velocity_body == lhs.angular_velocity_body) &&
           (rhs.pose_covariance == lhs.pose_covariance) &&
           (rhs.velocity_covariance == lhs.velocity_covariance);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Odometry const& odometry)
{
    str << std::setprecision(15);
    str << "odometry:" << '\n' << "{\n";
    str << "    time_usec: " << odometry.time_usec << '\n';
    str << "    frame_id: " << odometry.frame_id << '\n';
    str << "    child_frame_id: " << odometry.child_frame_id << '\n';
    str << "    position_body: " << odometry.position_body << '\n';
    str << "    q: " << odometry.q << '\n';
    str << "    velocity_body: " << odometry.velocity_body << '\n';
    str << "    angular_velocity_body: " << odometry.angular_velocity_body << '\n';
    str << "    pose_covariance: " << odometry.pose_covariance << '\n';
    str << "    velocity_covariance: " << odometry.velocity_covariance << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::DistanceSensor& lhs, const TelemetryServer::DistanceSensor& rhs)
{
    return ((std::isnan(rhs.minimum_distance_m) && std::isnan(lhs.minimum_distance_m)) ||
            rhs.minimum_distance_m == lhs.minimum_distance_m) &&
           ((std::isnan(rhs.maximum_distance_m) && std::isnan(lhs.maximum_distance_m)) ||
            rhs.maximum_distance_m == lhs.maximum_distance_m) &&
           ((std::isnan(rhs.current_distance_m) && std::isnan(lhs.current_distance_m)) ||
            rhs.current_distance_m == lhs.current_distance_m);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::DistanceSensor const& distance_sensor)
{
    str << std::setprecision(15);
    str << "distance_sensor:" << '\n' << "{\n";
    str << "    minimum_distance_m: " << distance_sensor.minimum_distance_m << '\n';
    str << "    maximum_distance_m: " << distance_sensor.maximum_distance_m << '\n';
    str << "    current_distance_m: " << distance_sensor.current_distance_m << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::ScaledPressure& lhs, const TelemetryServer::ScaledPressure& rhs)
{
    return (rhs.timestamp_us == lhs.timestamp_us) &&
           ((std::isnan(rhs.absolute_pressure_hpa) && std::isnan(lhs.absolute_pressure_hpa)) ||
            rhs.absolute_pressure_hpa == lhs.absolute_pressure_hpa) &&
           ((std::isnan(rhs.differential_pressure_hpa) &&
             std::isnan(lhs.differential_pressure_hpa)) ||
            rhs.differential_pressure_hpa == lhs.differential_pressure_hpa) &&
           ((std::isnan(rhs.temperature_deg) && std::isnan(lhs.temperature_deg)) ||
            rhs.temperature_deg == lhs.temperature_deg) &&
           ((std::isnan(rhs.differential_pressure_temperature_deg) &&
             std::isnan(lhs.differential_pressure_temperature_deg)) ||
            rhs.differential_pressure_temperature_deg == lhs.differential_pressure_temperature_deg);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::ScaledPressure const& scaled_pressure)
{
    str << std::setprecision(15);
    str << "scaled_pressure:" << '\n' << "{\n";
    str << "    timestamp_us: " << scaled_pressure.timestamp_us << '\n';
    str << "    absolute_pressure_hpa: " << scaled_pressure.absolute_pressure_hpa << '\n';
    str << "    differential_pressure_hpa: " << scaled_pressure.differential_pressure_hpa << '\n';
    str << "    temperature_deg: " << scaled_pressure.temperature_deg << '\n';
    str << "    differential_pressure_temperature_deg: "
        << scaled_pressure.differential_pressure_temperature_deg << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::PositionNed& lhs, const TelemetryServer::PositionNed& rhs)
{
    return ((std::isnan(rhs.north_m) && std::isnan(lhs.north_m)) || rhs.north_m == lhs.north_m) &&
           ((std::isnan(rhs.east_m) && std::isnan(lhs.east_m)) || rhs.east_m == lhs.east_m) &&
           ((std::isnan(rhs.down_m) && std::isnan(lhs.down_m)) || rhs.down_m == lhs.down_m);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::PositionNed const& position_ned)
{
    str << std::setprecision(15);
    str << "position_ned:" << '\n' << "{\n";
    str << "    north_m: " << position_ned.north_m << '\n';
    str << "    east_m: " << position_ned.east_m << '\n';
    str << "    down_m: " << position_ned.down_m << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::VelocityNed& lhs, const TelemetryServer::VelocityNed& rhs)
{
    return ((std::isnan(rhs.north_m_s) && std::isnan(lhs.north_m_s)) ||
            rhs.north_m_s == lhs.north_m_s) &&
           ((std::isnan(rhs.east_m_s) && std::isnan(lhs.east_m_s)) ||
            rhs.east_m_s == lhs.east_m_s) &&
           ((std::isnan(rhs.down_m_s) && std::isnan(lhs.down_m_s)) || rhs.down_m_s == lhs.down_m_s);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::VelocityNed const& velocity_ned)
{
    str << std::setprecision(15);
    str << "velocity_ned:" << '\n' << "{\n";
    str << "    north_m_s: " << velocity_ned.north_m_s << '\n';
    str << "    east_m_s: " << velocity_ned.east_m_s << '\n';
    str << "    down_m_s: " << velocity_ned.down_m_s << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::PositionVelocityNed& lhs,
    const TelemetryServer::PositionVelocityNed& rhs)
{
    return (rhs.position == lhs.position) && (rhs.velocity == lhs.velocity);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::PositionVelocityNed const& position_velocity_ned)
{
    str << std::setprecision(15);
    str << "position_velocity_ned:" << '\n' << "{\n";
    str << "    position: " << position_velocity_ned.position << '\n';
    str << "    velocity: " << position_velocity_ned.velocity << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::GroundTruth& lhs, const TelemetryServer::GroundTruth& rhs)
{
    return ((std::isnan(rhs.latitude_deg) && std::isnan(lhs.latitude_deg)) ||
            rhs.latitude_deg == lhs.latitude_deg) &&
           ((std::isnan(rhs.longitude_deg) && std::isnan(lhs.longitude_deg)) ||
            rhs.longitude_deg == lhs.longitude_deg) &&
           ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) ||
            rhs.absolute_altitude_m == lhs.absolute_altitude_m);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::GroundTruth const& ground_truth)
{
    str << std::setprecision(15);
    str << "ground_truth:" << '\n' << "{\n";
    str << "    latitude_deg: " << ground_truth.latitude_deg << '\n';
    str << "    longitude_deg: " << ground_truth.longitude_deg << '\n';
    str << "    absolute_altitude_m: " << ground_truth.absolute_altitude_m << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::FixedwingMetrics& lhs, const TelemetryServer::FixedwingMetrics& rhs)
{
    return ((std::isnan(rhs.airspeed_m_s) && std::isnan(lhs.airspeed_m_s)) ||
            rhs.airspeed_m_s == lhs.airspeed_m_s) &&
           ((std::isnan(rhs.throttle_percentage) && std::isnan(lhs.throttle_percentage)) ||
            rhs.throttle_percentage == lhs.throttle_percentage) &&
           ((std::isnan(rhs.climb_rate_m_s) && std::isnan(lhs.climb_rate_m_s)) ||
            rhs.climb_rate_m_s == lhs.climb_rate_m_s) &&
           ((std::isnan(rhs.groundspeed_m_s) && std::isnan(lhs.groundspeed_m_s)) ||
            rhs.groundspeed_m_s == lhs.groundspeed_m_s) &&
           ((std::isnan(rhs.heading_deg) && std::isnan(lhs.heading_deg)) ||
            rhs.heading_deg == lhs.heading_deg) &&
           ((std::isnan(rhs.absolute_altitude_m) && std::isnan(lhs.absolute_altitude_m)) ||
            rhs.absolute_altitude_m == lhs.absolute_altitude_m);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::FixedwingMetrics const& fixedwing_metrics)
{
    str << std::setprecision(15);
    str << "fixedwing_metrics:" << '\n' << "{\n";
    str << "    airspeed_m_s: " << fixedwing_metrics.airspeed_m_s << '\n';
    str << "    throttle_percentage: " << fixedwing_metrics.throttle_percentage << '\n';
    str << "    climb_rate_m_s: " << fixedwing_metrics.climb_rate_m_s << '\n';
    str << "    groundspeed_m_s: " << fixedwing_metrics.groundspeed_m_s << '\n';
    str << "    heading_deg: " << fixedwing_metrics.heading_deg << '\n';
    str << "    absolute_altitude_m: " << fixedwing_metrics.absolute_altitude_m << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::AccelerationFrd& lhs, const TelemetryServer::AccelerationFrd& rhs)
{
    return ((std::isnan(rhs.forward_m_s2) && std::isnan(lhs.forward_m_s2)) ||
            rhs.forward_m_s2 == lhs.forward_m_s2) &&
           ((std::isnan(rhs.right_m_s2) && std::isnan(lhs.right_m_s2)) ||
            rhs.right_m_s2 == lhs.right_m_s2) &&
           ((std::isnan(rhs.down_m_s2) && std::isnan(lhs.down_m_s2)) ||
            rhs.down_m_s2 == lhs.down_m_s2);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::AccelerationFrd const& acceleration_frd)
{
    str << std::setprecision(15);
    str << "acceleration_frd:" << '\n' << "{\n";
    str << "    forward_m_s2: " << acceleration_frd.forward_m_s2 << '\n';
    str << "    right_m_s2: " << acceleration_frd.right_m_s2 << '\n';
    str << "    down_m_s2: " << acceleration_frd.down_m_s2 << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::AngularVelocityFrd& lhs, const TelemetryServer::AngularVelocityFrd& rhs)
{
    return ((std::isnan(rhs.forward_rad_s) && std::isnan(lhs.forward_rad_s)) ||
            rhs.forward_rad_s == lhs.forward_rad_s) &&
           ((std::isnan(rhs.right_rad_s) && std::isnan(lhs.right_rad_s)) ||
            rhs.right_rad_s == lhs.right_rad_s) &&
           ((std::isnan(rhs.down_rad_s) && std::isnan(lhs.down_rad_s)) ||
            rhs.down_rad_s == lhs.down_rad_s);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::AngularVelocityFrd const& angular_velocity_frd)
{
    str << std::setprecision(15);
    str << "angular_velocity_frd:" << '\n' << "{\n";
    str << "    forward_rad_s: " << angular_velocity_frd.forward_rad_s << '\n';
    str << "    right_rad_s: " << angular_velocity_frd.right_rad_s << '\n';
    str << "    down_rad_s: " << angular_velocity_frd.down_rad_s << '\n';
    str << '}';
    return str;
}

bool operator==(
    const TelemetryServer::MagneticFieldFrd& lhs, const TelemetryServer::MagneticFieldFrd& rhs)
{
    return ((std::isnan(rhs.forward_gauss) && std::isnan(lhs.forward_gauss)) ||
            rhs.forward_gauss == lhs.forward_gauss) &&
           ((std::isnan(rhs.right_gauss) && std::isnan(lhs.right_gauss)) ||
            rhs.right_gauss == lhs.right_gauss) &&
           ((std::isnan(rhs.down_gauss) && std::isnan(lhs.down_gauss)) ||
            rhs.down_gauss == lhs.down_gauss);
}

std::ostream&
operator<<(std::ostream& str, TelemetryServer::MagneticFieldFrd const& magnetic_field_frd)
{
    str << std::setprecision(15);
    str << "magnetic_field_frd:" << '\n' << "{\n";
    str << "    forward_gauss: " << magnetic_field_frd.forward_gauss << '\n';
    str << "    right_gauss: " << magnetic_field_frd.right_gauss << '\n';
    str << "    down_gauss: " << magnetic_field_frd.down_gauss << '\n';
    str << '}';
    return str;
}

bool operator==(const TelemetryServer::Imu& lhs, const TelemetryServer::Imu& rhs)
{
    return (rhs.acceleration_frd == lhs.acceleration_frd) &&
           (rhs.angular_velocity_frd == lhs.angular_velocity_frd) &&
           (rhs.magnetic_field_frd == lhs.magnetic_field_frd) &&
           ((std::isnan(rhs.temperature_degc) && std::isnan(lhs.temperature_degc)) ||
            rhs.temperature_degc == lhs.temperature_degc) &&
           (rhs.timestamp_us == lhs.timestamp_us);
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Imu const& imu)
{
    str << std::setprecision(15);
    str << "imu:" << '\n' << "{\n";
    str << "    acceleration_frd: " << imu.acceleration_frd << '\n';
    str << "    angular_velocity_frd: " << imu.angular_velocity_frd << '\n';
    str << "    magnetic_field_frd: " << imu.magnetic_field_frd << '\n';
    str << "    temperature_degc: " << imu.temperature_degc << '\n';
    str << "    timestamp_us: " << imu.timestamp_us << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::Result const& result)
{
    switch (result) {
        case TelemetryServer::Result::Unknown:
            return str << "Unknown";
        case TelemetryServer::Result::Success:
            return str << "Success";
        case TelemetryServer::Result::NoSystem:
            return str << "No System";
        case TelemetryServer::Result::ConnectionError:
            return str << "Connection Error";
        case TelemetryServer::Result::Busy:
            return str << "Busy";
        case TelemetryServer::Result::CommandDenied:
            return str << "Command Denied";
        case TelemetryServer::Result::Timeout:
            return str << "Timeout";
        case TelemetryServer::Result::Unsupported:
            return str << "Unsupported";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::FixType const& fix_type)
{
    switch (fix_type) {
        case TelemetryServer::FixType::NoGps:
            return str << "No Gps";
        case TelemetryServer::FixType::NoFix:
            return str << "No Fix";
        case TelemetryServer::FixType::Fix2D:
            return str << "Fix 2D";
        case TelemetryServer::FixType::Fix3D:
            return str << "Fix 3D";
        case TelemetryServer::FixType::FixDgps:
            return str << "Fix Dgps";
        case TelemetryServer::FixType::RtkFloat:
            return str << "Rtk Float";
        case TelemetryServer::FixType::RtkFixed:
            return str << "Rtk Fixed";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::VtolState const& vtol_state)
{
    switch (vtol_state) {
        case TelemetryServer::VtolState::Undefined:
            return str << "Undefined";
        case TelemetryServer::VtolState::TransitionToFw:
            return str << "Transition To Fw";
        case TelemetryServer::VtolState::TransitionToMc:
            return str << "Transition To Mc";
        case TelemetryServer::VtolState::Mc:
            return str << "Mc";
        case TelemetryServer::VtolState::Fw:
            return str << "Fw";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::StatusTextType const& status_text_type)
{
    switch (status_text_type) {
        case TelemetryServer::StatusTextType::Debug:
            return str << "Debug";
        case TelemetryServer::StatusTextType::Info:
            return str << "Info";
        case TelemetryServer::StatusTextType::Notice:
            return str << "Notice";
        case TelemetryServer::StatusTextType::Warning:
            return str << "Warning";
        case TelemetryServer::StatusTextType::Error:
            return str << "Error";
        case TelemetryServer::StatusTextType::Critical:
            return str << "Critical";
        case TelemetryServer::StatusTextType::Alert:
            return str << "Alert";
        case TelemetryServer::StatusTextType::Emergency:
            return str << "Emergency";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, TelemetryServer::LandedState const& landed_state)
{
    switch (landed_state) {
        case TelemetryServer::LandedState::Unknown:
            return str << "Unknown";
        case TelemetryServer::LandedState::OnGround:
            return str << "On Ground";
        case TelemetryServer::LandedState::InAir:
            return str << "In Air";
        case TelemetryServer::LandedState::TakingOff:
            return str << "Taking Off";
        case TelemetryServer::LandedState::Landing:
            return str << "Landing";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk