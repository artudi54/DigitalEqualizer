#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol {
    class TimeChangedMessage : public Message {
    public:
        MessageType getMessageType() const override;
        std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;

        float currentTime;
        float totalTime;
    };
}