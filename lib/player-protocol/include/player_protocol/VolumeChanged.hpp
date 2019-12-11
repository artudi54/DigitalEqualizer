#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class VolumeChanged : public Message {
    public:
        MessageType getMessageType() const override;
        std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;

        std::uint32_t volume;
    };
}
