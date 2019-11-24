#include <stdexcept>
#include <sys/Application.hpp>
#include <audio/filter/DigitalEqualizerFilter.hpp>
#include <audio/AudioPlayer.hpp>
#include <filesystem/DirectoryListing.hpp>


int main() {
    try {
        sys::Application application;
        filesystem::DirectoryListing listing("0:/");
        audio::filter::DigitalEqualizerFilter filter;
        audio::AudioPlayer audioPlayer;
        audioPlayer.setAudioFilter(filter);
        audioPlayer.setSource("0:/sample");
        audioPlayer.setVolume(60);
        audioPlayer.play();
        return application.exec();
    }
    catch (std::exception &exc) {
        exc.what();
    }
}
