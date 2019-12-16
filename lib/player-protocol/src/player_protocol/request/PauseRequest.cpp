#include "PauseRequest.hpp"

namespace player_protocol::request {
    MessageType PauseRequest::getMessageType() const {
        return MessageType::REQUEST_PAUSE;
    }

    void PauseRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }
}