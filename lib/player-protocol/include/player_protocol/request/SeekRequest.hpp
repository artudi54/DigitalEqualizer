#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::request {
    class SeekRequest : public Message {
    public:
        SeekRequest();
        explicit SeekRequest(float position);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] float getPosition() const;
        void setPosition(float position);

    private:
        float position;
    };
}
