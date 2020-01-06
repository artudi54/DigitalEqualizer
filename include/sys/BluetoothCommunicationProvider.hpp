#pragma once
#include <array>
#include <cstdint>

namespace sys {
    class BluetoothCommunicationProvider {
    public:
        BluetoothCommunicationProvider();
        [[nodiscard]] bool hasSizedMessage() const;
        void transmitSizedMessage(const char* bytes, std::uint32_t length);
        void receiveSizedMessage(char* bytes);

    private:
        [[nodiscard]] std::uint32_t getIncomingDataSize() const;
        void copyCircullar(void* destination, std::uint32_t length);

        std::array<char, 1024> buffer;
        std::size_t position;
    };
}
