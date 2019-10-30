#pragma once

namespace sys {
    class Application {
        friend class Handlers;
    public:
        Application();
        int exec();

    private:
        void initializeHAL();

        void initializeClock();

        void initializeLED();

        void initializeStdIO();

        void initializeSDCard();
        void initializeSDCardSPI();
        void initializeSDCardSPICS();
        void initializeSDCardSPIIO();
        void initializeSDCardFatFS();

        void sysTickHandler();
        void errorHandler();

        static Application* instance;
    };

}