#pragma once
#include <string>
#include <player_protocol/Message.hpp>

namespace player_protocol::response {
    class ErrorResponse : public Message {
    public:
        ErrorResponse();
        explicit ErrorResponse(const std::string &errorMessage);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor& visitor) const override;

        [[nodiscard]] const std::string &getErrorMessage() const;
        void setErrorMessage(const std::string &errorMessage);

    private:
        std::string errorMessage;
    };
}
