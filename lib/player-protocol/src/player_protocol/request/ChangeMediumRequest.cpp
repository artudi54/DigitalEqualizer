#include "ChangeMediumRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    ChangeMediumRequest::ChangeMediumRequest()
        : newMedium() {}

    ChangeMediumRequest::ChangeMediumRequest(const std::string &newMedium)
        : newMedium(newMedium) {}

    MessageType ChangeMediumRequest::getMessageType() const {
        return MessageType::REQUEST_CHANGE_MEDIUM;
    }

    std::uint32_t ChangeMediumRequest::serialize(char *data) const {
        std::uint32_t offset = 0;
        std::uint32_t stringLength = static_cast<std::uint32_t>(newMedium.size());

        std::memcpy(data + offset, &stringLength, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        std::memcpy(data + offset, newMedium.c_str(), stringLength);
        offset += stringLength;

        return offset;
    }

    void ChangeMediumRequest::deserialize(const char *data) {
        std::uint32_t offset = 0;
        std::uint32_t stringLength;

        std::memcpy(&stringLength, data + offset, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        newMedium.resize(stringLength);
        std::memcpy(newMedium.data(), data + offset, stringLength);
        offset += stringLength;
    }

    void ChangeMediumRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    const std::string &ChangeMediumRequest::getNewMedium() const {
        return newMedium;
    }

    void ChangeMediumRequest::setNewMedium(const std::string &newMedium) {
        this->newMedium = newMedium;
    }
}