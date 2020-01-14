#pragma once
#include <audio/AudioPlayer.hpp>
#include <audio/Playlist.hpp>

namespace  audio {
    class PlaylistPlayer {
    public:
        explicit PlaylistPlayer(const std::string& directoryPath);

        void play();
        void pause();
        void stop();
        void seek(float time);

        [[nodiscard]] std::int32_t getCurrentTrackNumber() const;
        void setCurrentTrackNumber(std::uint32_t trackNumber);

        [[nodiscard]] unsigned getVolume() const;
        void setVolume(unsigned volume);

        void setAudioFilter(filter::AudioFilter& filter);

        [[nodiscard]] const Playlist& getPlaylist() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] bool isPlaying() const;
        [[nodiscard]] bool isPaused() const;
        [[nodiscard]] bool isStopped() const;
        [[nodiscard]] AudioPlayer::State getState() const;

        [[nodiscard]] float getCurrentTime() const;
        [[nodiscard]] float getEndTime() const;

        void setOnStateChanged(const std::function<void(AudioPlayer::State)>& onStateChanged);
        void setOnProgressChanged(const std::function<void(float,float)>& onProgressChanged);
        void setOnMediumChanged(const std::function<void(const std::string&)>& onMediumChanged);
        void setOnVolumeChanged(const std::function<void(unsigned)>& onVolumeChanged);

    private:
        void handleTimeChanged(float currentTime, float totalTime);

        Playlist playlist;
        AudioPlayer player;
        std::function<void(float,float)> onProgressChanged;
        std::int32_t currentTrackNumber;
    };
}