#pragma once
#include <audio/AudioPlayer.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>

namespace service {
    class NotificationService {
    public:
        explicit NotificationService(sys::BluetoothCommunicationProvider& communicationProvider);
        void initializeCallbacks(audio::AudioPlayer& player);
    private:
        void handleTimeChanged(float currentTime, float totalTime);
        void handleMediumChanged(const std::string& medium);
        void handleVolumeChanged(std::uint32_t volume);

        sys::BluetoothCommunicationProvider& communicationProvider;
        std::array<char, 256> buffer;
    };
}
