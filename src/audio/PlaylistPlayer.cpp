#include "PlaylistPlayer.hpp"

namespace audio {

    PlaylistPlayer::PlaylistPlayer(const std::string &directoryPath)
        : playlist(directoryPath)
        , player()
        , onProgressChanged()
        , currentTrackNumber(-1) {
        player.setOnProgressChanged([this](float currentTime, float totalTime) {
            handleTimeChanged(currentTime, totalTime);
        });
    }

    void PlaylistPlayer::play() {
        player.play();
    }

    void PlaylistPlayer::pause() {
        player.pause();
    }

    void PlaylistPlayer::stop() {
        player.stop();
    }

    void PlaylistPlayer::seek(float time) {
        player.seek(time);
    }

    std::int32_t PlaylistPlayer::getCurrentTrackNumber() const {
        return currentTrackNumber;
    }

    void PlaylistPlayer::setCurrentTrackNumber(std::uint32_t trackNumber) {
        player.setSource(playlist.getAudioFilePathAt(trackNumber));
        currentTrackNumber = trackNumber;
    }

    unsigned PlaylistPlayer::getVolume() const {
        return player.getVolume();
    }

    void PlaylistPlayer::setVolume(unsigned volume) {
        player.setVolume(volume);
    }

    void PlaylistPlayer::setAudioFilter(filter::AudioFilter &filter) {
        player.setAudioFilter(filter);
    }

    const Playlist& PlaylistPlayer::getPlaylist() const {
        return playlist;
    }

    bool PlaylistPlayer::isEmpty() const {
        return player.isEmpty();
    }

    bool PlaylistPlayer::isPlaying() const {
        return player.isPlaying();
    }

    bool PlaylistPlayer::isPaused() const {
        return player.isPaused();
    }

    bool PlaylistPlayer::isStopped() const {
        return player.isStopped();
    }

    AudioPlayer::State PlaylistPlayer::getState() const {
        return player.getState();
    }

    float PlaylistPlayer::getCurrentTime() const {
        return player.getCurrentTime();
    }

    float PlaylistPlayer::getEndTime() const {
        return player.getEndTime();
    }

    void PlaylistPlayer::setOnProgressChanged(const std::function<void(float, float)> &onProgressChanged) {
        this->onProgressChanged = onProgressChanged;
    }

    void PlaylistPlayer::setOnMediumChanged(const std::function<void(const std::string &)> &onMediumChanged) {
        player.setOnMediumChanged(onMediumChanged);
    }

    void PlaylistPlayer::setOnVolumeChanged(const std::function<void(unsigned)> &onVolumeChanged) {
        player.setOnVolumeChanged(onVolumeChanged);
    }

    void PlaylistPlayer::handleTimeChanged(float currentTime, float totalTime) {
        if (onProgressChanged != nullptr)
            onProgressChanged(currentTime, totalTime);

        if (currentTime == totalTime && static_cast<std::size_t>(currentTrackNumber) != playlist.getAudioFileCount() - 1) {
            setCurrentTrackNumber(currentTrackNumber + 1);
            play();
        }
    }
}