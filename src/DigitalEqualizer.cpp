#include "DigitalEqualizer.hpp"

DigitalEqualizer::DigitalEqualizer()
    : playlistPlayer("0:/")
    , filter()
    , communicationProvider()
    , notificationService(communicationProvider)
    , requestHandler(communicationProvider, playlistPlayer, filter) {
    notificationService.initializeCallbacks(playlistPlayer);
    notificationService.initializeCallbacks(filter);
    playlistPlayer.setAudioFilter(filter);

}