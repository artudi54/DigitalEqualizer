#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class PlayRequest : public Message {
    public:
        MessageType getMessageType() const override;

        uint32_t serialize(char *data) const override;

        void deserialize(const char *data) override;
    };
}
