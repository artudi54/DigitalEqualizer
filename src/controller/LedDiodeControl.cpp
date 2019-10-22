#include "LedDiodeControl.hpp"
#include <cstdint>
#include <stdexcept>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

namespace controller {
    static std::uint16_t getPin(LedDiodeControl::Color color) {
        switch (color)  {
            case LedDiodeControl::Color::Green:
                return GPIO_Pin_12;
            case LedDiodeControl::Color::Orange:
                return GPIO_Pin_13;
            case LedDiodeControl::Color::Red:
                return GPIO_Pin_14;
            case LedDiodeControl::Color::Blue:
                return GPIO_Pin_15;
            default:
                throw std::invalid_argument("Invalid diode color");
        }
    }

    LedDiodeControl& LedDiodeControl::getInstance() {
        static LedDiodeControl ledDiodeControl;
        return ledDiodeControl;
    }

    void LedDiodeControl::enableDiode(LedDiodeControl::Color color) {
        GPIO_WriteBit(GPIOD, getPin(color), Bit_SET);
    }

    void LedDiodeControl::disableDiode(LedDiodeControl::Color color) {
        GPIO_WriteBit(GPIOD, getPin(color), Bit_RESET);
    }

    LedDiodeControl::LedDiodeControl() {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        GPIO_InitTypeDef gpio;
        gpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        gpio.GPIO_Mode = GPIO_Mode_OUT;
        gpio.GPIO_Speed = GPIO_High_Speed;
        gpio.GPIO_OType = GPIO_OType_PP;
        gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOD, &gpio);
    }
}