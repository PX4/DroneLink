/**
 * @file follow_me.cpp
 *
 * @brief Example that demonstrates the usage of Follow Me plugin.
 * The example registers with FakeLocationProvider for location updates
 * and sends them to the Follow Me plugin which are sent to drone. You can observe
 * drone following you. We print last location of the drone in flight mode callback.
 *
 * @author Shakthi Prashanth <shakthi.prashanth.m@intel.com>
 * @date 2018-01-03
 */

#include <chrono>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/follow_me/follow_me.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <future>
#include <iostream>
#include <memory>
#include <thread>

#include "fake_location_provider.h"

using namespace mavsdk;
using namespace std::placeholders; // for `_1`
using namespace std::chrono; // for seconds(), milliseconds(), etc
using namespace std::this_thread; // for sleep_for()

// For coloring output
#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

inline void action_error_exit(Action::Result result, const std::string& message);
inline void follow_me_error_exit(FollowMe::Result result, const std::string& message);
inline void connection_error_exit(ConnectionResult result, const std::string& message);
inline void wait_until_discover(Mavsdk& mavsdk);

void usage(std::string bin_name)
{
    std::cout << NORMAL_CONSOLE_TEXT << "Usage : " << bin_name << " <connection_url>" << std::endl
              << "Connection URL format should be :" << std::endl
              << " For TCP : tcp://[server_host][:server_port]" << std::endl
              << " For UDP : udp://[bind_host][:bind_port]" << std::endl
              << " For Serial : serial:///path/to/serial/dev[:baudrate]" << std::endl
              << "For example, to connect to the simulator use URL: udp://:14540" << std::endl;
}

int main(int argc, char** argv)
{
    Mavsdk mavsdk;
    std::string connection_url;
    ConnectionResult connection_result;

    if (argc == 2) {
        connection_url = argv[1];
        connection_result = mavsdk.add_any_connection(connection_url);
    } else {
        usage(argv[0]);
        return 1;
    }

    if (connection_result != ConnectionResult::Success) {
        std::cout << ERROR_CONSOLE_TEXT << "Connection failed: " << connection_result
                  << NORMAL_CONSOLE_TEXT << std::endl;
        return 1;
    }

    wait_until_discover(mavsdk);

    // System got discovered.
    auto system = mavsdk.systems().at(0);
    auto action = std::make_shared<Action>(system);
    auto follow_me = std::make_shared<FollowMe>(system);
    auto telemetry = std::make_shared<Telemetry>(system);

    while (!telemetry->health_all_ok()) {
        std::cout << "Waiting for system to be ready" << std::endl;
        sleep_for(seconds(1));
    }
    std::cout << "System is ready" << std::endl;

    // Arm
    Action::Result arm_result = action->arm();
    action_error_exit(arm_result, "Arming failed");
    std::cout << "Armed" << std::endl;

    // Subscribe to receive updates on flight mode. You can find out whether FollowMe is active.
    telemetry->subscribe_flight_mode(std::bind(
        [&](Telemetry::FlightMode flight_mode) {
            const FollowMe::TargetLocation last_location = follow_me->get_last_location();
            std::cout << "[FlightMode: " << flight_mode
                      << "] Vehicle is at: " << last_location.latitude_deg << ", "
                      << last_location.longitude_deg << " degrees." << std::endl;
        },
        std::placeholders::_1));

    // Takeoff
    Action::Result takeoff_result = action->takeoff();
    action_error_exit(takeoff_result, "Takeoff failed");
    std::cout << "In Air..." << std::endl;
    sleep_for(seconds(5)); // Wait for drone to reach takeoff altitude

    // Configure Min height of the drone to be "20 meters" above home & Follow direction as "Front
    // right".
    FollowMe::Config config;
    config.min_height_m = 10.0;
    config.follow_direction = FollowMe::Config::FollowDirection::Behind;
    FollowMe::Result follow_me_result = follow_me->set_config(config);

    // Start Follow Me
    follow_me_result = follow_me->start();
    follow_me_error_exit(follow_me_result, "Failed to start FollowMe mode");

    FakeLocationProvider location_provider;
    // Register for platform-specific Location provider. We're using FakeLocationProvider for the
    // example.
    location_provider.request_location_updates([&follow_me](double lat, double lon) {
        FollowMe::TargetLocation target_location{};
        target_location.latitude_deg = lat;
        target_location.longitude_deg = lon;
        follow_me->set_target_location(target_location);
    });

    while (location_provider.is_running()) {
        sleep_for(seconds(1));
    }

    // Stop Follow Me
    follow_me_result = follow_me->stop();
    follow_me_error_exit(follow_me_result, "Failed to stop FollowMe mode");

    // Stop flight mode updates.
    telemetry->subscribe_flight_mode(nullptr);

    // Land
    const Action::Result land_result = action->land();
    action_error_exit(land_result, "Landing failed");
    while (telemetry->in_air()) {
        std::cout << "waiting until landed" << std::endl;
        sleep_for(seconds(1));
    }
    std::cout << "Landed..." << std::endl;
    return 0;
}

void wait_until_discover(Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system..." << std::endl;
    std::promise<void> discover_promise;
    auto discover_future = discover_promise.get_future();

    mavsdk.subscribe_on_new_system([&mavsdk, &discover_promise]() {
        const auto system = mavsdk.systems().at(0);

        if (system->is_connected()) {
            std::cout << "Discovered system" << std::endl;
            discover_promise.set_value();
        }
    });

    discover_future.wait();
}

// Handles Action's result
inline void action_error_exit(Action::Result result, const std::string& message)
{
    if (result != Action::Result::Success) {
        std::cerr << ERROR_CONSOLE_TEXT << message << result << NORMAL_CONSOLE_TEXT << std::endl;
        exit(EXIT_FAILURE);
    }
}
// Handles FollowMe's result
inline void follow_me_error_exit(FollowMe::Result result, const std::string& message)
{
    if (result != FollowMe::Result::Success) {
        std::cerr << ERROR_CONSOLE_TEXT << message << result << NORMAL_CONSOLE_TEXT << std::endl;
        exit(EXIT_FAILURE);
    }
}
// Handles connection result
inline void connection_error_exit(ConnectionResult result, const std::string& message)
{
    if (result != ConnectionResult::Success) {
        std::cerr << ERROR_CONSOLE_TEXT << message << result << NORMAL_CONSOLE_TEXT << std::endl;
        exit(EXIT_FAILURE);
    }
}
