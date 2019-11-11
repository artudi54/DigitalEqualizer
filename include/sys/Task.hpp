#pragma once

namespace sys {
    class Task {
    public:
        Task();
        virtual ~Task();
        virtual void progress() = 0;
    };
}