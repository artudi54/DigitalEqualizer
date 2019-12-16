#include "ChangeVolumeRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    ChangeVolumeRequest::ChangeVolumeRequest()
            : newVolume(0) {}

    ChangeVolumeRequest::ChangeVolumeRequest(std::uint32_t newVolume)
        : newVolume(newVolume) {}

    MessageType ChangeVolumeRequest::getMessageType() const {
        return MessageType::REQUEST_CHANGE_VOLUME;
    }

    std::uint32_t ChangeVolumeRequest::serialize(char *data) const {
        std::memcpy(data, &newVolume, sizeof(std::uint32_t));
        return sizeof(std::uint32_t);
    }

    void ChangeVolumeRequest::deserialize(const char *data) {
        std::memcpy(&newVolume, data, sizeof(std::uint32_t));
    }

    void ChangeVolumeRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    std::uint32_t ChangeVolumeRequest::getNewVolume() const {
        return newVolume;
    }

    void ChangeVolumeRequest::setNewVolume(std::uint32_t newVolume) {
        this->newVolume = newVolume;
    }
}