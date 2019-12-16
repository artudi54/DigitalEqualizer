#include "PlayRequest.hpp"

namespace player_protocol::request {
    MessageType PlayRequest::getMessageType() const {
        return MessageType::REQUEST_PLAY;
    }

    std::uint32_t PlayRequest::serialize(char *data) const {
        (void)data;
        return 0;
    }

    void PlayRequest::deserialize(const char *data) {
        (void)data;
    }
}