#pragma once
#include <cstdint>

namespace player_protocol {
    enum class MessageType : std::uint8_t {
        CHANGED_MEDIUM,
        CHANGED_TIME,
        CHANGED_VOLUME,

        REQUEST_CHANGE_MEDIUM,
        REQUEST_CHANGE_VOLUME,
        REQUEST_FAST_FORWARD,
        REQUEST_PAUSE,
        REQUEST_PLAY,
        REQUEST_STOP,

        RESPONSE_OK,
        RESPONSE_ERROR
    };
}
