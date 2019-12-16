#pragma once
#include <cstddef>
#include <player_protocol/MessageType.hpp>
#include <player_protocol/MessageVisitor.hpp>

namespace player_protocol {
    class Message {
    public:
        virtual ~Message();
        [[nodiscard]] virtual MessageType getMessageType() const = 0;
        [[nodiscard]] virtual std::uint32_t serialize(char* data) const = 0;
        virtual void deserialize(const char* data) = 0;
        virtual void visit(MessageVisitor& visitor) const = 0;
    };

    class EmptyMessage : public Message {
    public:
        [[nodiscard]] std::uint32_t serialize(char* data) const final;
        void deserialize(const char* data) final;
    };
}