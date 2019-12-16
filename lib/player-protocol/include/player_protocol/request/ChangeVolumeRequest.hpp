#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::request {
    class ChangeVolumeRequest : public Message {
    public:
        ChangeVolumeRequest();
        explicit ChangeVolumeRequest(std::uint32_t newVolume);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] std::uint32_t getNewVolume() const;
        void setNewVolume(std::uint32_t newVolume);

    private:
        std::uint32_t newVolume;
    };
}