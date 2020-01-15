#pragma once
#include <audio/PlaylistPlayer.hpp>
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>

namespace service {
    class NotificationService {
    public:
        explicit NotificationService(sys::BluetoothCommunicationProvider& communicationProvider);
        void initializeCallbacks(audio::PlaylistPlayer& player);
        void initializeCallbacks(audio::filter::DigitalEqualizerFilter& filter);
    private:
        void handleStateChanged(audio::AudioPlayer::State state);
        void handleTimeChanged(float currentTime, float totalTime);
        void handleMediumChanged(const std::string& medium);
        void handleVolumeChanged(std::uint32_t volume);
        void handleEqualizerParametersChanged(const audio::filter::DigitalEqualizerParameters& parameters);

        sys::BluetoothCommunicationProvider& communicationProvider;
        std::array<char, 256> buffer;
    };
}
