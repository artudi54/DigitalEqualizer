#include "DigitalEqualizer.hpp"

DigitalEqualizer::DigitalEqualizer()
    : playlistPlayer("0:/")
    , filter()
    , communicationProvider()
    , notificationService(communicationProvider)
    , requestHandler(communicationProvider, playlistPlayer) {
    setupFilter();
    notificationService.initializeCallbacks(playlistPlayer);
}

void DigitalEqualizer::setupFilter() {
    audio::filter::DigitalEqualizerParameters parameters;
    parameters.setFrequenciesType(audio::filter::DigitalEqualizerParameters::FrequenciesType::ISOOctave);
    filter.setParameters(parameters);
    playlistPlayer.setAudioFilter(filter);
}
