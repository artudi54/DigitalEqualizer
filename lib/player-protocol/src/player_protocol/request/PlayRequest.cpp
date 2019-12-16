#include "PlayRequest.hpp"

namespace player_protocol::request {
    MessageType PlayRequest::getMessageType() const {
        return MessageType::REQUEST_PLAY;
    }
}