#include "LedDiodeControl.hpp"
#include <cstdint>
#include <stdexcept>
#include <stm32f4xx_hal_gpio.h>

namespace sys {
    bool LedDiodeControl::isEnabled(LedDiodeColor color) {
        return HAL_GPIO_ReadPin(GPIOD, getPIN(color)) == GPIO_PIN_SET;
    }

    void LedDiodeControl::enableDiode(LedDiodeColor color) {
        HAL_GPIO_WritePin(GPIOD, getPIN(color), GPIO_PIN_SET);
    }

    void LedDiodeControl::disableDiode(LedDiodeColor color) {
        HAL_GPIO_WritePin(GPIOD, getPIN(color), GPIO_PIN_RESET);
    }

    void LedDiodeControl::toggleDiode(LedDiodeColor color) {
        HAL_GPIO_TogglePin(GPIOD, getPIN(color));
    }

    std::uint16_t LedDiodeControl::getPIN(LedDiodeColor color) {
        switch (color)  {
            case LedDiodeColor::Green:
                return GPIO_PIN_12;
            case LedDiodeColor::Orange:
                return GPIO_PIN_13;
            case LedDiodeColor::Red:
                return GPIO_PIN_14;
            case LedDiodeColor::Blue:
                return GPIO_PIN_15;
            default:
                throw std::invalid_argument("Invalid diode color");
        }
    }
}