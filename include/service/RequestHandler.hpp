#pragma once
#include <array>
#include <audio/AudioPlayer.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <sys/Task.hpp>

namespace service {
    class RequestHandler : public sys::Task {
    public:
        RequestHandler(sys::BluetoothCommunicationProvider& communicationProvider, audio::AudioPlayer& player);

        void progress() override;
    private:
        void handlePlay();
        void handlePause();
        sys::BluetoothCommunicationProvider& communicationProvider;
        audio::AudioPlayer& player;
        std::array<char, 256> buffer;
    };
}