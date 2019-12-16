#include "PauseRequest.hpp"

namespace player_protocol::request {
    MessageType PauseRequest::getMessageType() const {
        return MessageType::REQUEST_PAUSE;
    }
}