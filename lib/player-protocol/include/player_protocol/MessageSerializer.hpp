#pragma once
#include <memory>
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class MessageSerializer {
    public:
        static std::uint32_t serialize(const Message &message, char* data);
        static std::unique_ptr<Message> deserialize(const char* data);
    };
}
