#include "Task.hpp"
#include <sys/Application.hpp>

namespace sys {

    Task::Task() {
        Application::instance->registerTask(this);
    }

    Task::~Task() {
        Application::instance->unregisterTask(this);
    }
}