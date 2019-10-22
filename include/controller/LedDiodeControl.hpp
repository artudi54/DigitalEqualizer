#pragma once

namespace controller {
    class LedDiodeControl {
    public:
        enum class Color {
            Green,
            Orange,
            Red,
            Blue
        };

        static LedDiodeControl& getInstance();
        void enableDiode(Color color);
        void disableDiode(Color color);
    private:
        LedDiodeControl();
    };
}