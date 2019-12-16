#include "PauseRequest.hpp"

namespace player_protocol::request {

    MessageType PauseRequest::getMessageType() const {
        return MessageType::REQUEST_PAUSE;
    }

    std::uint32_t PauseRequest::serialize(char *data) const {
        (void)data;
        return 0;
    }

    void PauseRequest::deserialize(const char *data) {
        (void)data;
    }
}