#include "DigitalEqualizer.hpp"

DigitalEqualizer::DigitalEqualizer()
    : playlistPlayer("0:/")
    , filter()
    , communicationProvider()
    , notificationService(communicationProvider)
    , requestHandler(communicationProvider, playlistPlayer) {
    setupFilter();
    notificationService.initializeCallbacks(playlistPlayer);
    playlistPlayer.setCurrentTrackNumber(0);
    playlistPlayer.setVolume(100);
}

void DigitalEqualizer::setupFilter() {
    audio::filter::DigitalEqualizerParameters parameters;
    parameters.setFrequenciesType(audio::filter::DigitalEqualizerParameters::FrequenciesType::ISOOctave);
    filter.setParameters(parameters);
    playlistPlayer.setAudioFilter(filter);
}
