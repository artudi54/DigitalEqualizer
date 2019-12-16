#include "OkResponse.hpp"

namespace player_protocol::response {

    MessageType OkResponse::getMessageType() const {
        return MessageType::RESPONSE_OK;
    }

    std::uint32_t OkResponse::serialize(char *data) const {
        (void)data;
        return 0;
    }

    void OkResponse::deserialize(const char *data) {
        (void)data;
    }
}