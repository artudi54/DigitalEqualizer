#include <sys/Application.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <audio/PlaylistPlayer.hpp>
#include <service/NotificationService.hpp>
#include <service/RequestHandler.hpp>

int main() {
    try {
        sys::Application application;

        audio::PlaylistPlayer playlistPlayer("0:/");
        audio::filter::DigitalEqualizerFilter filter;
        sys::BluetoothCommunicationProvider communicationProvider;
        service::NotificationService notificationService(communicationProvider);
        service::RequestHandler requestHandler(communicationProvider, playlistPlayer);


        audio::filter::DigitalEqualizerParameters parameters;
        parameters.setFrequenciesType(audio::filter::DigitalEqualizerParameters::FrequenciesType::ISOOctave);
        parameters.setDbGainAt(0, 5);
        parameters.setDbGainAt(1, 5);
        parameters.setDbGainAt(2, 5);
        filter.setParameters(parameters);
        playlistPlayer.setAudioFilter(filter);

        notificationService.initializeCallbacks(playlistPlayer);


        playlistPlayer.setCurrentTrackNumber(1);
        playlistPlayer.setVolume(70);
        playlistPlayer.play();


        return application.exec();
    }
    catch (std::exception &exc) {
        exc.what();
    }
}
