#include <controller/LedDiodeControl.hpp>
extern "C" int main() {
	controller::LedDiodeControl& control = controller::LedDiodeControl::getInstance();
	control.enableDiode(controller::LedDiodeControl::Color::Red);
	control.enableDiode(controller::LedDiodeControl::Color::Green);
    while (true);
    return 0;
}      
