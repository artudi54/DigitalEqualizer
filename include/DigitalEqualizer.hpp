#pragma once
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <audio/PlaylistPlayer.hpp>
#include <service/NotificationService.hpp>
#include <service/RequestHandler.hpp>

class DigitalEqualizer {
public:
    DigitalEqualizer();

private:
    audio::PlaylistPlayer playlistPlayer;
    audio::filter::DigitalEqualizerFilter filter;

    sys::BluetoothCommunicationProvider communicationProvider;
    service::NotificationService notificationService;
    service::RequestHandler requestHandler;
};