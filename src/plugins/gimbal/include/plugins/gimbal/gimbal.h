// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/gimbal/gimbal.proto)

#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "plugin_base.h"

namespace mavsdk {

class System;
class GimbalImpl;

/**
 * @brief Provide control over a gimbal.
 */
class Gimbal : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto gimbal = std::make_shared<Gimbal>(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit Gimbal(System& system);

    /**
     * @brief Destructor (internal use only).
     */
    ~Gimbal();

    /**
     * @brief Gimbal mode type.
     */
    enum class GimbalMode {
        YawFollow, /**< @brief Yaw follow will point the gimbal to the vehicle heading. */
        YawLock, /**< @brief Yaw lock will fix the gimbal poiting to an absolute direction. */
    };

    /**
     * @brief Stream operator to print information about a `Gimbal::GimbalMode`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Gimbal::GimbalMode const& gimbal_mode);

    /**
     * @brief Possible results returned for gimbal commands.
     */
    enum class Result {
        Unknown, /**< @brief Unknown error. */
        Success, /**< @brief Command was accepted. */
        Error, /**< @brief Error occurred sending the command. */
        Timeout, /**< @brief Command timed out. */
    };

    /**
     * @brief Stream operator to print information about a `Gimbal::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Gimbal::Result const& result);

    /**
     * @brief Callback type for asynchronous Gimbal calls.
     */
    typedef std::function<void(Result)> ResultCallback;

    /**
     * @brief Set gimbal pitch and yaw angles.
     *
     * This sets the desired pitch and yaw angles of a gimbal.
     * Will return when the command is accepted, however, it might
     * take the gimbal longer to actually be set to the new angles.
     *
     * This function is non-blocking. See 'set_pitch_and_yaw' for the blocking counterpart.
     */
    void set_pitch_and_yaw_async(float pitch_deg, float yaw_deg, const ResultCallback callback);

    /**
     * @brief Set gimbal pitch and yaw angles.
     *
     * This sets the desired pitch and yaw angles of a gimbal.
     * Will return when the command is accepted, however, it might
     * take the gimbal longer to actually be set to the new angles.
     *
     * This function is blocking. See 'set_pitch_and_yaw_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result set_pitch_and_yaw(float pitch_deg, float yaw_deg) const;

    /**
     * @brief Set gimbal mode.
     *
     * This sets the desired yaw mode of a gimbal.
     * Will return when the command is accepted. However, it might
     * take the gimbal longer to actually be set to the new angles.
     *
     * This function is non-blocking. See 'set_mode' for the blocking counterpart.
     */
    void set_mode_async(GimbalMode gimbal_mode, const ResultCallback callback);

    /**
     * @brief Set gimbal mode.
     *
     * This sets the desired yaw mode of a gimbal.
     * Will return when the command is accepted. However, it might
     * take the gimbal longer to actually be set to the new angles.
     *
     * This function is blocking. See 'set_mode_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result set_mode(GimbalMode gimbal_mode) const;

    /**
     * @brief Set gimbal region of interest (ROI).
     *
     * This sets a region of interest that the gimbal will point to.
     * The gimbal will continue to point to the specified region until it
     * receives a new command.
     * The function will return when the command is accepted, however, it might
     * take the gimbal longer to actually rotate to the ROI.
     *
     * This function is non-blocking. See 'set_roi_location' for the blocking counterpart.
     */
    void set_roi_location_async(
        double latitude_deg, double longitude_deg, float altitude_m, const ResultCallback callback);

    /**
     * @brief Set gimbal region of interest (ROI).
     *
     * This sets a region of interest that the gimbal will point to.
     * The gimbal will continue to point to the specified region until it
     * receives a new command.
     * The function will return when the command is accepted, however, it might
     * take the gimbal longer to actually rotate to the ROI.
     *
     * This function is blocking. See 'set_roi_location_async' for the non-blocking counterpart.
     *
     * @return Result of request.
     */
    Result set_roi_location(double latitude_deg, double longitude_deg, float altitude_m) const;

    /**
     * @brief Returns a human-readable English string for a Result.
     *
     * @param result The enum value for which a human readable string is required.
     * @return Human readable string for the Result.
     */
    static const char* result_str(Result result);

    /**
     * @brief Copy constructor (object is not copyable).
     */
    Gimbal(const Gimbal&) = delete;

    /**
     * @brief Equality operator (object is not copyable).
     */
    const Gimbal& operator=(const Gimbal&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<GimbalImpl> _impl;
};

} // namespace mavsdk