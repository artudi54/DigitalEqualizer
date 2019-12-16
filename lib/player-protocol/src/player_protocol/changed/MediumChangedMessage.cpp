#include "MediumChangedMessage.hpp"
#include <cstring>

namespace player_protocol::changed {

    MessageType MediumChangedMessage::getMessageType() const {
        return MessageType::CHANGED_MEDIUM;
    }

    std::uint32_t MediumChangedMessage::serialize(char *data) const {
        std::uint32_t offset = 0;
        std::uint32_t stringLength = static_cast<std::uint32_t>(medium.size());

        std::memcpy(data + offset, &stringLength, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        std::memcpy(data + offset, medium.c_str(), stringLength);
        offset += stringLength;

        return offset;
    }

    void MediumChangedMessage::deserialize(const char *data) {
        std::uint32_t offset = 0;
        std::uint32_t stringLength;

        std::memcpy(&stringLength, data + offset, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        medium.resize(stringLength);
        std::memcpy(medium.data(), data + offset, stringLength);
        offset += stringLength;
    }

    void MediumChangedMessage::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }
}