#include <sys/Application.hpp>
#include <audio/filter/AudioFilter.hpp>
#include <audio/AudioPlayer.hpp>
#include <filesystem/DirectoryListing.hpp>


int main() {
    sys::Application application;
    filesystem::DirectoryListing listing("0:/");
    audio::filter::AudioFilter filter;
    audio::AudioPlayer audioPlayer;
    audioPlayer.setAudioFilter(filter);
    audioPlayer.setSource("0:/sample");
    audioPlayer.setVolume(60);
    audioPlayer.play();
    return application.exec();
}


