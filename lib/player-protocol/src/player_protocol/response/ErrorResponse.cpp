#include "ErrorResponse.hpp"
#include <cstring>

namespace player_protocol::response {
    ErrorResponse::ErrorResponse()
        : errorMessage() {}

    ErrorResponse::ErrorResponse(const std::string &errorMessage)
        : errorMessage(errorMessage) {}

    MessageType ErrorResponse::getMessageType() const {
        return MessageType::RESPONSE_ERROR;
    }

    uint32_t ErrorResponse::serialize(char *data) const {
        std::uint32_t offset = 0;
        std::uint32_t stringLength = static_cast<std::uint32_t>(errorMessage.size());

        std::memcpy(data + offset, &stringLength, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        std::memcpy(data + offset, errorMessage.c_str(), stringLength);
        offset += stringLength;

        return offset;
    }

    void ErrorResponse::deserialize(const char *data) {
        std::uint32_t offset = 0;
        std::uint32_t stringLength;

        std::memcpy(&stringLength, data + offset, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        errorMessage.resize(stringLength);
        std::memcpy(errorMessage.data(), data + offset, stringLength);
        offset += stringLength;
    }

    void ErrorResponse::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    const std::string &ErrorResponse::getErrorMessage() const {
        return errorMessage;
    }

    void ErrorResponse::setErrorMessage(const std::string &errorMessage) {
        this->errorMessage = errorMessage;
    }
}