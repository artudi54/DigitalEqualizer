#include "SeekRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    SeekRequest::SeekRequest()
        : position(0.0f) {}

    SeekRequest::SeekRequest(float position)
        : position(position) {}

    MessageType SeekRequest::getMessageType() const {
        return MessageType::REQUEST_SEEK;
    }

    std::uint32_t SeekRequest::serialize(char *data) const {
        std::memcpy(data, &position, sizeof(float));
        return sizeof(float);
    }

    void SeekRequest::deserialize(const char *data) {
        std::memcpy(&position, data, sizeof(float));
    }

    void SeekRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    float SeekRequest::getPosition() const {
        return position;
    }

    void SeekRequest::setPosition(float position) {
        this->position = position;
    }
}