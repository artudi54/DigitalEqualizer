#pragma once
#include <vector>
#include <sys/Task.hpp>

namespace sys {
    class Application {
        friend class Handlers;
        friend class Task;
    public:
        Application();
        int exec();

    protected:
        void registerTask(Task* task);
        void unregisterTask(Task* task);
    private:
        void initializeHAL();

        void initializeClock();
        void initializeSDCard();
        void initializeSDCardSPI();
        void initializeSDCardSPICS();
        void initializeSDCardSPIIO();
        void initializeSDCardFatFS();

        void sysTickHandler();
        void errorHandler();

        static Application* instance;

        std::vector<Task*> tasks;
    };

}
