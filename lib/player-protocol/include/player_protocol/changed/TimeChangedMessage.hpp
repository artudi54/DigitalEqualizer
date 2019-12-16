#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::changed {
    class TimeChangedMessage : public Message {
    public:
        TimeChangedMessage();
        TimeChangedMessage(float currentTime, float totalTime);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] float getCurrentTime() const;
        void setCurrentTime(float currentTime);
        [[nodiscard]] float getTotalTime() const;
        void setTotalTime(float totalTime);

    private:
        float currentTime;
        float totalTime;
    };
}