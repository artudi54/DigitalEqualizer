#include <controller/LedDiodeControl.hpp>
#include <chrono>

namespace controller {
    class Application {
    public:
        int exec();
        static Application& createInstance();

        static LedDiodeControl& getLedDiodeControl();
        static void sleep(std::chrono::milliseconds milliseconds);
    private:
        Application();
        volatile bool working;
    };
}