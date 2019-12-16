#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::response {
    class OkResponse : public Message {
    public:
        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
    };
}