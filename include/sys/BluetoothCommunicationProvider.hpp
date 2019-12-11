#pragma once
#include <vector>
#include <cstddef>

namespace sys {
    class BluetoothCommunicationProvider {
    public:
        BluetoothCommunicationProvider();
        void transmitMessage(const char* bytes, std::size_t length);
        void receiveMessage(char* bytes, std::size_t length);
    };
}
