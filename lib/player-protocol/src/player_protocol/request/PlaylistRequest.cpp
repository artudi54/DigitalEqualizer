#include "PlaylistRequest.hpp"

namespace player_protocol::request {

    MessageType PlaylistRequest::getMessageType() const {
        return MessageType::REQUEST_PLAYLIST;
    }

    void PlaylistRequest::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }
}