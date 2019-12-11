#pragma once
#include <cstdint>

namespace sys {
    class BluetoothCommunicationProvider {
    public:
        BluetoothCommunicationProvider();
        bool hasSizedMessage();
        void transmitSizedMessage(const char* bytes, std::uint32_t length);
        void receiveSizedMessage(char* bytes);
    };
}
