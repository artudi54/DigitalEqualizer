#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::changed {
    class VolumeChangedMessage : public Message {
    public:
        VolumeChangedMessage();
        explicit VolumeChangedMessage(std::uint32_t volume);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] std::uint32_t getVolume() const;
        void setVolume(uint32_t volume);

    private:
        std::uint32_t volume;
    };
}
