// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/main/protos/param_server/param_server.proto)

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
class ParamServerImpl;

/**
 * @brief Provide raw access to retrieve and provide server parameters.
 */
class ParamServer : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto param_server = ParamServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit ParamServer(System& system); // deprecated

    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto param_server = ParamServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit ParamServer(std::shared_ptr<System> system); // new

    /**
     * @brief Destructor (internal use only).
     */
    ~ParamServer();

    /**
     * @brief Type for integer parameters.
     */
    struct IntParam {
        std::string name{}; /**< @brief Name of the parameter */
        int32_t value{}; /**< @brief Value of the parameter */
    };

    /**
     * @brief Equal operator to compare two `ParamServer::IntParam` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const ParamServer::IntParam& lhs, const ParamServer::IntParam& rhs);

    /**
     * @brief Stream operator to print information about a `ParamServer::IntParam`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, ParamServer::IntParam const& int_param);

    /**
     * @brief Type for float parameters.
     */
    struct FloatParam {
        std::string name{}; /**< @brief Name of the parameter */
        float value{}; /**< @brief Value of the parameter */
    };

    /**
     * @brief Equal operator to compare two `ParamServer::FloatParam` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const ParamServer::FloatParam& lhs, const ParamServer::FloatParam& rhs);

    /**
     * @brief Stream operator to print information about a `ParamServer::FloatParam`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, ParamServer::FloatParam const& float_param);

    /**
     * @brief Type collecting all integer and float parameters.
     */
    struct AllParams {
        std::vector<IntParam>
            int_params{}; /**< @brief Collection of all parameter names and values of type int */
        std::vector<FloatParam> float_params{}; /**< @brief Collection of all parameter names and
                                                   values of type float */
    };

    /**
     * @brief Equal operator to compare two `ParamServer::AllParams` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const ParamServer::AllParams& lhs, const ParamServer::AllParams& rhs);

    /**
     * @brief Stream operator to print information about a `ParamServer::AllParams`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, ParamServer::AllParams const& all_params);

    /**
     * @brief Possible results returned for param requests.
     */
    enum class Result {
        Unknown, /**< @brief Unknown result. */
        Success, /**< @brief Request succeeded. */
        NotFound, /**< @brief Not Found. */
        WrongType, /**< @brief Wrong type. */
        ParamNameTooLong, /**< @brief Parameter name too long (> 16). */
    };

    /**
     * @brief Stream operator to print information about a `ParamServer::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, ParamServer::Result const& result);

    /**
     * @brief Callback type for asynchronous ParamServer calls.
     */
    using ResultCallback = std::function<void(Result)>;

    /**
     * @brief Retrieve an int parameter.
     *
     * If the type is wrong, the result will be `WRONG_TYPE`.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    std::pair<Result, int32_t> retrieve_param_int(std::string name) const;

    /**
     * @brief Provide an int parameter.
     *
     * If the type is wrong, the result will be `WRONG_TYPE`.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result provide_param_int(std::string name, int32_t value) const;

    /**
     * @brief Retrieve a float parameter.
     *
     * If the type is wrong, the result will be `WRONG_TYPE`.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    std::pair<Result, float> retrieve_param_float(std::string name) const;

    /**
     * @brief Provide a float parameter.
     *
     * If the type is wrong, the result will be `WRONG_TYPE`.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result provide_param_float(std::string name, float value) const;

    /**
     * @brief Retrieve all parameters.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    ParamServer::AllParams retrieve_all_params() const;

    /**
     * @brief Copy constructor.
     */
    ParamServer(const ParamServer& other);

    /**
     * @brief Equality operator (object is not copyable).
     */
    const ParamServer& operator=(const ParamServer&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<ParamServerImpl> _impl;
};

} // namespace mavsdk