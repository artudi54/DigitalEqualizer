#pragma once

namespace player_protocol {
    enum class MessageType {
        REQUEST,
        RESPONSE,
        PERIODIC,
        ERROR_INDICATOR
    };
}
