#include "PlayRequest.hpp"

namespace player_protocol::request {
    MessageType PlayRequest::getMessageType() const {
        return MessageType::REQUEST_PLAY;
    }

    void PlayRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }
}