#pragma once
#include <string>
#include <player_protocol/Message.hpp>

namespace player_protocol::changed {
    class MediumChangedMessage : public Message {
    public:
        MediumChangedMessage();
        explicit MediumChangedMessage(const std::string& medium);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] const std::string &getMedium() const;
        void setMedium(const std::string &medium);

    private:
        std::string medium;
    };
}
