// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see
// https://github.com/mavlink/MAVSDK-Proto/blob/main/protos/mission_server/mission_server.proto)

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
class MissionServerImpl;

/**
 * @brief Enable waypoint missions.
 */
class MissionServer : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto mission_server = MissionServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit MissionServer(System& system); // deprecated

    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto mission_server = MissionServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit MissionServer(std::shared_ptr<System> system); // new

    /**
     * @brief Destructor (internal use only).
     */
    ~MissionServer();

    /**
     * @brief Mission item exactly identical to MAVLink MISSION_ITEM_INT.
     */
    struct MissionItem {
        uint32_t seq{}; /**< @brief Sequence (uint16_t) */
        uint32_t frame{}; /**< @brief The coordinate system of the waypoint (actually uint8_t) */
        uint32_t command{}; /**< @brief The scheduled action for the waypoint (actually uint16_t) */
        uint32_t current{}; /**< @brief false:0, true:1 (actually uint8_t) */
        uint32_t autocontinue{}; /**< @brief Autocontinue to next waypoint (actually uint8_t) */
        float param1{}; /**< @brief PARAM1, see MAV_CMD enum */
        float param2{}; /**< @brief PARAM2, see MAV_CMD enum */
        float param3{}; /**< @brief PARAM3, see MAV_CMD enum */
        float param4{}; /**< @brief PARAM4, see MAV_CMD enum */
        int32_t x{}; /**< @brief PARAM5 / local: x position in meters * 1e4, global: latitude in
                        degrees * 10^7 */
        int32_t y{}; /**< @brief PARAM6 / y position: local: x position in meters * 1e4, global:
                        longitude in degrees *10^7 */
        float z{}; /**< @brief PARAM7 / local: Z coordinate, global: altitude (relative or absolute,
                      depending on frame) */
        uint32_t mission_type{}; /**< @brief Mission type (actually uint8_t) */
    };

    /**
     * @brief Equal operator to compare two `MissionServer::MissionItem` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool
    operator==(const MissionServer::MissionItem& lhs, const MissionServer::MissionItem& rhs);

    /**
     * @brief Stream operator to print information about a `MissionServer::MissionItem`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, MissionServer::MissionItem const& mission_item);

    /**
     * @brief Mission plan type
     */
    struct MissionPlan {
        std::vector<MissionItem> mission_items{}; /**< @brief The mission items */
    };

    /**
     * @brief Equal operator to compare two `MissionServer::MissionPlan` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool
    operator==(const MissionServer::MissionPlan& lhs, const MissionServer::MissionPlan& rhs);

    /**
     * @brief Stream operator to print information about a `MissionServer::MissionPlan`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, MissionServer::MissionPlan const& mission_plan);

    /**
     * @brief Mission progress type.
     */
    struct MissionProgress {
        int32_t current{}; /**< @brief Current mission item index (0-based), if equal to total, the
                              mission is finished */
        int32_t total{}; /**< @brief Total number of mission items */
    };

    /**
     * @brief Equal operator to compare two `MissionServer::MissionProgress` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(
        const MissionServer::MissionProgress& lhs, const MissionServer::MissionProgress& rhs);

    /**
     * @brief Stream operator to print information about a `MissionServer::MissionProgress`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream&
    operator<<(std::ostream& str, MissionServer::MissionProgress const& mission_progress);

    /**
     * @brief Possible results returned for action requests.
     */
    enum class Result {
        Unknown, /**< @brief Unknown result. */
        Success, /**< @brief Request succeeded. */
        Error, /**< @brief Error. */
        TooManyMissionItems, /**< @brief Too many mission items in the mission. */
        Busy, /**< @brief Vehicle is busy. */
        Timeout, /**< @brief Request timed out. */
        InvalidArgument, /**< @brief Invalid argument. */
        Unsupported, /**< @brief Mission downloaded from the system is not supported. */
        NoMissionAvailable, /**< @brief No mission available on the system. */
        UnsupportedMissionCmd, /**< @brief Unsupported mission command. */
        TransferCancelled, /**< @brief Mission transfer (upload or download) has been cancelled. */
        NoSystem, /**< @brief No system connected. */
    };

    /**
     * @brief Stream operator to print information about a `MissionServer::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, MissionServer::Result const& result);

    /**
     * @brief Callback type for asynchronous MissionServer calls.
     */
    using ResultCallback = std::function<void(Result)>;

    /**
     * @brief Callback type for subscribe_incoming_mission.
     */

    using IncomingMissionCallback = std::function<void(MissionServer::Result, MissionPlan)>;

    /**
     * @brief Subscribe to when a new mission is uploaded (asynchronous).
     */
    void subscribe_incoming_mission(IncomingMissionCallback callback);

    /**
     * @brief Poll for 'MissionPlan' (blocking).
     *
     * @return One MissionPlan update.
     */
    MissionPlan incoming_mission() const;

    /**
     * @brief Callback type for subscribe_current_item_changed.
     */

    using CurrentItemChangedCallback = std::function<void(MissionItem)>;

    /**
     * @brief Subscribe to when a new current item is set
     */
    void subscribe_current_item_changed(CurrentItemChangedCallback callback);

    /**
     * @brief Poll for 'MissionItem' (blocking).
     *
     * @return One MissionItem update.
     */
    MissionItem current_item_changed() const;

    /**
     * @brief Set Current item as completed
     *
     * This function is non-blocking. See 'set_current_item_complete' for the blocking counterpart.
     */
    void set_current_item_complete_async(const ResultCallback callback);

    /**
     * @brief Set Current item as completed
     *
     * This function is blocking. See 'set_current_item_complete_async' for the non-blocking
     * counterpart.
     *
     * @return Result of request.
     */
    void set_current_item_complete() const;

    /**
     * @brief Callback type for subscribe_clear_all.
     */

    using ClearAllCallback = std::function<void(uint32_t)>;

    /**
     * @brief Subscribe when a MISSION_CLEAR_ALL is received
     */
    void subscribe_clear_all(ClearAllCallback callback);

    /**
     * @brief Poll for 'uint32_t' (blocking).
     *
     * @return One uint32_t update.
     */
    uint32_t clear_all() const;

    /**
     * @brief Copy constructor.
     */
    MissionServer(const MissionServer& other);

    /**
     * @brief Equality operator (object is not copyable).
     */
    const MissionServer& operator=(const MissionServer&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<MissionServerImpl> _impl;
};

} // namespace mavsdk