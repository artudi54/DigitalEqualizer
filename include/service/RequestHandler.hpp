#pragma once
#include <array>
#include <audio/PlaylistPlayer.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <sys/Task.hpp>

namespace service {
    class RequestHandler : public sys::Task {
    public:
        RequestHandler(sys::BluetoothCommunicationProvider& communicationProvider, audio::PlaylistPlayer& player);

        void progress() override;
    private:
        void handlePlay();
        void handlePause();
        sys::BluetoothCommunicationProvider& communicationProvider;
        audio::PlaylistPlayer& player;
        std::array<char, 256> buffer;
    };
}