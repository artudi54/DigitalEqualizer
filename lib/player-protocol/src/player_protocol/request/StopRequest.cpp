#include "StopRequest.hpp"

namespace player_protocol::request {
    MessageType StopRequest::getMessageType() const {
        return MessageType::REQUEST_STOP;
    }
}