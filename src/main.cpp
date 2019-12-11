#include <sys/Application.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <audio/AudioPlayer.hpp>
#include <audio/Playlist.hpp>
#include <service/NotificationService.hpp>
#include <service/RequestHandler.hpp>

int main() {
    try {
        sys::Application application;
        audio::Playlist listing("0:/");


        audio::AudioPlayer audioPlayer;
        audio::filter::DigitalEqualizerFilter filter;
        sys::BluetoothCommunicationProvider communicationProvider;
        service::NotificationService notificationService(communicationProvider);
        service::RequestHandler requestHandler(communicationProvider, audioPlayer);

        audio::filter::DigitalEqualizerParameters parameters;
        parameters.setFrequenciesType(audio::filter::DigitalEqualizerParameters::FrequenciesType::ISOOctave);
        parameters.setDbGainAt(0, -10);
        parameters.setDbGainAt(1, -10);
        parameters.setDbGainAt(2, -10);
        filter.setParameters(parameters);
        audioPlayer.setAudioFilter(filter);


        notificationService.initializeCallbacks(audioPlayer);


        audioPlayer.setSource("0:/sample16k.wav");
        audioPlayer.setVolume(60);
//        audioPlayer.play();


        return application.exec();
    }
    catch (std::exception &exc) {
        exc.what();
    }
}
