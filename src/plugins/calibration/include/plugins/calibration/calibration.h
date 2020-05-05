// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/calibration/calibration.proto)

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
class CalibrationImpl;

/**
 * @brief Enable to calibrate sensors of a drone such as gyro, accelerometer, and magnetometer.
 */
class Calibration : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto calibration = std::make_shared<Calibration>(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit Calibration(System& system);

    /**
     * @brief Destructor (internal use only).
     */
    ~Calibration();

    /**
     * @brief Possible results returned for calibration commands
     */
    enum class Result {
        Unknown, /**< @brief Unknown error. */
        Success, /**< @brief The calibration process succeeded. */
        Next, /**< @brief Intermediate message showing progress or instructions on the next steps
                 required by the process. */
        Failed, /**< @brief Calibration failed. */
        NoSystem, /**< @brief No system is connected. */
        ConnectionError, /**< @brief Connection error. */
        Busy, /**< @brief Vehicle is busy. */
        CommandDenied, /**< @brief Command refused by vehicle. */
        Timeout, /**< @brief Command timed out. */
        Cancelled, /**< @brief Calibration process got cancelled. */
    };

    /**
     * @brief Stream operator to print information about a `Calibration::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, Calibration::Result const& result);

    /**
     * @brief Progress data coming from calibration.
     *
     * Can be a progress percentage, or an instruction text.
     */
    struct ProgressData {
        bool has_progress{
            false}; /**< @brief Whether this ProgressData contains a 'progress' status or not */
        float progress{float(NAN)}; /**< @brief Progress (percentage) */
        bool has_status_text{
            false}; /**< @brief Whether this ProgressData contains a 'status_text' or not */
        std::string status_text{}; /**< @brief Instruction text */
    };

    /**
     * @brief Equal operator to compare two `Calibration::ProgressData` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool
    operator==(const Calibration::ProgressData& lhs, const Calibration::ProgressData& rhs);

    /**
     * @brief Stream operator to print information about a `Calibration::ProgressData`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, Calibration::ProgressData const& progress_data);

    /**
     * @brief Callback type for asynchronous Calibration calls.
     */
    typedef std::function<void(Result)> ResultCallback;

    /**
     * @brief Callback type for calibrate_gyro_async.
     */

    typedef std::function<void(Calibration::Result, ProgressData)> CalibrateGyroCallback;

    /**
     * @brief Perform gyro calibration.
     */
    void calibrate_gyro_async(CalibrateGyroCallback callback);

    /**
     * @brief Callback type for calibrate_accelerometer_async.
     */

    typedef std::function<void(Calibration::Result, ProgressData)> CalibrateAccelerometerCallback;

    /**
     * @brief Perform accelerometer calibration.
     */
    void calibrate_accelerometer_async(CalibrateAccelerometerCallback callback);

    /**
     * @brief Callback type for calibrate_magnetometer_async.
     */

    typedef std::function<void(Calibration::Result, ProgressData)> CalibrateMagnetometerCallback;

    /**
     * @brief Perform magnetometer caliration.
     */
    void calibrate_magnetometer_async(CalibrateMagnetometerCallback callback);

    /**
     * @brief Callback type for calibrate_gimbal_accelerometer_async.
     */

    typedef std::function<void(Calibration::Result, ProgressData)>
        CalibrateGimbalAccelerometerCallback;

    /**
     * @brief Perform gimbal accelerometer calibration.
     */
    void calibrate_gimbal_accelerometer_async(CalibrateGimbalAccelerometerCallback callback);

    /**
     * @brief Cancel ongoing calibration process.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    void cancel() const;

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
    Calibration(const Calibration&) = delete;

    /**
     * @brief Equality operator (object is not copyable).
     */
    const Calibration& operator=(const Calibration&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<CalibrationImpl> _impl;
};

} // namespace mavsdk