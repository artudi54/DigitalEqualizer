#pragma once
#include <memory>
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class MessageFactory {
    public:
        [[nodiscard]] static std::unique_ptr<Message> create(MessageType type);
    };
}
