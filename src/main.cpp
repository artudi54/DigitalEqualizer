#include <controller/LedDiodeControl.hpp>
#include <controller/Application.hpp>
using namespace std::literals;

extern "C" int main() {
    controller::Application& application = controller::Application::createInstance();
	controller::LedDiodeControl& control = controller::Application::getLedDiodeControl();
	controller::Application::sleep(1s);
	control.enableDiode(controller::LedDiodeControl::Color::Red);
	controller::Application::sleep(1s);
	control.enableDiode(controller::LedDiodeControl::Color::Green);
	controller::Application::sleep(1s);
	control.disableDiode(controller::LedDiodeControl::Color::Red);
	controller::Application::sleep(1s);
	control.disableDiode(controller::LedDiodeControl::Color::Green);
    return application.exec();
}      
