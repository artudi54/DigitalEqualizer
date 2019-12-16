#pragma once
#include <cstddef>
#include <player_protocol/MessageType.hpp>

namespace player_protocol {
    class Message {
    public:
        virtual ~Message();
        [[nodiscard]] virtual MessageType getMessageType() const = 0;
        [[nodiscard]] virtual std::uint32_t serialize(char* data) const = 0;
        virtual void deserialize(const char* data) = 0;
    };
}