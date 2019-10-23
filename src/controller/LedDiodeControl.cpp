#include "LedDiodeControl.hpp"
#include <cstdint>
#include <stdexcept>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>

namespace controller {
    static std::uint16_t getPIN(LedDiodeControl::Color color) {
        switch (color)  {
            case LedDiodeControl::Color::Green:
                return GPIO_PIN_12;
            case LedDiodeControl::Color::Orange:
                return GPIO_PIN_13;
            case LedDiodeControl::Color::Red:
                return GPIO_PIN_14;
            case LedDiodeControl::Color::Blue:
                return GPIO_PIN_15;
            default:
                throw std::invalid_argument("Invalid diode color");
        }
    }

    LedDiodeControl& LedDiodeControl::getInstance() {
        static LedDiodeControl ledDiodeControl;
        return ledDiodeControl;
    }

    void LedDiodeControl::enableDiode(LedDiodeControl::Color color) {
        HAL_GPIO_WritePin(GPIOD, getPIN(color), GPIO_PIN_SET);
    }

    void LedDiodeControl::disableDiode(LedDiodeControl::Color color) {
        HAL_GPIO_WritePin(GPIOD, getPIN(color), GPIO_PIN_RESET);
    }

    LedDiodeControl::LedDiodeControl() {
		HAL_Init();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        GPIO_InitTypeDef gpio;
        gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        gpio.Mode = GPIO_MODE_OUTPUT_PP;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOD, &gpio);
    }
}