#include <sys/Application.hpp>
#include <sys/BluetoothCommunicationProvider.hpp>
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <audio/AudioPlayer.hpp>
#include <audio/Playlist.hpp>
#include <stm32f4xx_hal.h>

int main() {
    try {
        sys::Application application;
        sys::BluetoothCommunicationProvider provider;
        std::string message = "AT+NAMEDigitalEqualizer";
        provider.transmitMessage(message.c_str(), message.size());
        std::string data(6, 0);
        provider.receiveMessage(data.data(), 6);

        audio::Playlist listing("0:/");
        audio::filter::DigitalEqualizerFilter filter;
        audio::filter::DigitalEqualizerParameters parameters;
        parameters.setFrequenciesType(audio::filter::DigitalEqualizerParameters::FrequenciesType::ISOOctave);
        parameters.setDbGainAt(0, -10);
        parameters.setDbGainAt(1, -10);
        filter.setParameters(parameters);

        audio::AudioPlayer audioPlayer;
        audioPlayer.setAudioFilter(filter);
        audioPlayer.setSource("0:/sample8k.wav");
        audioPlayer.setVolume(60);
        audioPlayer.play();

        return application.exec();
    }
    catch (std::exception &exc) {
        exc.what();
    }
}
