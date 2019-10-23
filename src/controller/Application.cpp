#include "Application.hpp"
#include <stm32f4xx_hal.h>

/* Interrupt handlers */
extern "C" {
    // Sleep functionality
    void SysTick_Handler() {
        HAL_IncTick();
    }
}

namespace controller {

    Application &Application::createInstance() {
        static Application application;
        return application;
    }

    LedDiodeControl &Application::getLedDiodeControl() {
        return LedDiodeControl::getInstance();
    }

    Application::Application()
        : working(true) {
        HAL_Init();
    }

    int Application::exec() {
        while (working);
        return 0;
    }

    void Application::sleep(std::chrono::milliseconds milliseconds) {
        HAL_Delay(static_cast<std::uint32_t>(milliseconds.count()));
    }
}