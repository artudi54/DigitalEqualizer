#pragma once
#include <cstdint>

namespace player_protocol {
    enum class MessageType : std::uint8_t {
        MEDIUM_CHANGED,
        TIME_CHANGED,
        VOLUME_CHANGED,

        PLAY_REQUEST
    };
}
