#include "OkResponse.hpp"

namespace player_protocol::response {
    MessageType OkResponse::getMessageType() const {
        return MessageType::RESPONSE_OK;
    }

    void OkResponse::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }
}