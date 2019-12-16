#pragma once
#include <string>
#include <player_protocol/Message.hpp>

namespace player_protocol::request {
    class ChangeMediumRequest : public Message {
    public:
        ChangeMediumRequest();
        explicit ChangeMediumRequest(const std::string &newMedium);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] const std::string &getNewMedium() const;
        void setNewMedium(const std::string &newMedium);

    private:
        std::string newMedium;
    };
}
