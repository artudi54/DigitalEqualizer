#include "Message.hpp"

namespace player_protocol {
    Message::~Message() = default;


    std::uint32_t EmptyMessage::serialize(char *data) const {
        (void)data;
        return 0;
    }

    void EmptyMessage::deserialize(const char *data) {
        (void)data;
    }
}