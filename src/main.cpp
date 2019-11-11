#include <sys/Application.hpp>
#include <filesystem/DirectoryListing.hpp>
#include <audio/AudioPlayer.hpp>


int main() {
    sys::Application application;
    filesystem::DirectoryListing listing("0:/");
    audio::AudioPlayer audioPlayer;
    audioPlayer.setSource("0:/sample");
    audioPlayer.setVolume(60);
    audioPlayer.play();
    return application.exec();
}


