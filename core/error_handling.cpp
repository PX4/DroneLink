#include "error_handling.h"

namespace dronecore {

const char *result_str(Result res)
{
    switch (res) {
        case Result::SUCCESS:
            return "Succes";
        case Result::TIMEOUT:
            return "Timeout";
        case Result::WRONG_ARGUMENT:
            return "Wrong argument";
        case Result::CONNECTION_ERROR:
            return "Connection error";
        case Result::NOT_IMPLEMENTED:
            return "Not implemented";
        case Result::DEVICE_NOT_CONNECTED:
            return "Device not connected";
        case Result::DEVICE_BUSY:
            return "Device busy";
        case Result::COMMAND_DENIED:
            return "Command denied";
        case Result::DESTINATION_IP_UNKNOWN:
            return "Destination IP unknown";
        default:
            return "Unknown error";
    }
}

} // namespace dronecore
