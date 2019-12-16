#include "StopRequest.hpp"

namespace player_protocol::request {

    MessageType StopRequest::getMessageType() const {
        return MessageType::REQUEST_STOP;
    }

    std::uint32_t StopRequest::serialize(char *data) const {
        (void)data;
        return 0;
    }

    void StopRequest::deserialize(const char *data) {
        (void)data;
    }
}