#pragma once
#include <array>
#include <player_protocol/MessageVisitor.hpp>
#include <audio/PlaylistPlayer.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <sys/Task.hpp>

namespace service {
    class RequestHandler : private sys::Task , private player_protocol::MessageServerVisitor {
    public:
        RequestHandler(sys::BluetoothCommunicationProvider& communicationProvider, audio::PlaylistPlayer& player);

    private:
        void progress() override;

        void handleMessage(const player_protocol::request::ChangeMediumRequest& message) override;
        void handleMessage(const player_protocol::request::ChangeVolumeRequest& message) override;
        void handleMessage(const player_protocol::request::PauseRequest& message) override;
        void handleMessage(const player_protocol::request::PlaylistRequest& message) override;
        void handleMessage(const player_protocol::request::PlayRequest& message) override;
        void handleMessage(const player_protocol::request::SeekRequest& message) override;
        void handleMessage(const player_protocol::request::StopRequest& message) override;
        void handleInvalidMessage(const player_protocol::Message &message) override;

        void sendMessage(const player_protocol::Message& message);

        sys::BluetoothCommunicationProvider& communicationProvider;
        audio::PlaylistPlayer& player;
        std::array<char, 256> buffer;
    };
}