#pragma once
#include <memory>
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class MessageSerializer {
    public:
        [[nodiscard]] static std::uint32_t serialize(const Message &message, char* data);
        [[nodiscard]] static std::unique_ptr<Message> deserialize(const char* data);
    };
}
