#include <sys/Application.hpp>
#include <DigitalEqualizer.hpp>

int main() {
    try {
        sys::Application application;
        DigitalEqualizer equalizer;
        return application.exec();
    }
    catch (std::exception &exc) {
        exc.what();
    }
}
