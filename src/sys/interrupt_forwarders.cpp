#include <sys/Application.hpp>

namespace sys {
    class Handlers {
    public:
        static void handleSysTick() {
            sys::Application::instance->sysTickHandler();
        }
        static void handleError() {
            sys::Application::instance->errorHandler();
        }
    };
}

extern "C" void SysTick_Handler(void) {
    sys::Handlers::handleSysTick();
}

extern "C" void Error_Handler(void) {
    sys::Handlers::handleError();
}