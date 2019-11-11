#pragma once
#include <cstdint>

namespace sys {
    enum class LedDiodeColor {
        Green,
        Orange,
        Red,
        Blue
    };

    class LedDiodeControl {
    public:
        explicit LedDiodeControl();
        bool isEnabled(LedDiodeColor color);
        void enableDiode(LedDiodeColor color);
        void disableDiode(LedDiodeColor color);
        void toggleDiode(LedDiodeColor color);
    private:
        static std::uint16_t getPIN(LedDiodeColor color);
    };
}