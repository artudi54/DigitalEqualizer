#pragma once
#include <functional>
#include <memory>
#include <string>
#include <audio/filter/AudioFilter.hpp>
#include <audio/WavAudioReader.hpp>
#include <sys/Task.hpp>

namespace audio {
    class AudioPlayer : public sys::Task {
        friend class Handlers;
    public:
        enum class State {
            //TODO: move state to new file
            NO_SOURCE,
            STOPPED,
            PLAYING,
            PAUSED
        };

        AudioPlayer();
        ~AudioPlayer() override;
        void setSource(const std::string& sourcePath);
        void unloadSource();
        void play();
        void pause();
        void stop();
        void seek(float time);

        [[nodiscard]] unsigned getVolume() const; // TODO: make std::uint32_t
        void setVolume(unsigned volume);

        void setAudioFilter(filter::AudioFilter& filter);

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] bool isPlaying() const;
        [[nodiscard]] bool isPaused() const;
        [[nodiscard]] bool isStopped() const;
        [[nodiscard]] State getState() const;

        [[nodiscard]] float getCurrentTime() const;
        [[nodiscard]] float getEndTime() const;

        void setOnStateChanged(const std::function<void(State)>& onStateChanged);
        void setOnProgressChanged(const std::function<void(float,float)>& onProgressChanged);
        void setOnMediumChanged(const std::function<void(const std::string&)>& onMediumChanged);
        void setOnVolumeChanged(const std::function<void(unsigned)>& onVolumeChanged);

    private:
        enum class BufferState {
            Done,
            Started,
            HalfWayThrough,
            Error
        };

        void progress() override;
        void updateState(State state);

        void playerInitialize();
        void playerDeinitialize();
        void playerPlayBuffer();
        void playerSetVolume();
        void playerPause();
        void playerUnpause();

        void handleError();
        void handleBufferHalfWay();
        void handleBufferDone();

        void validateNotEmpty();

        State state;
        BufferState bufferState;
        unsigned volume;
        std::unique_ptr<WavAudioReader> reader;
        std::vector<std::uint16_t> playingBuffer;
        std::vector<std::uint16_t> cachedBuffer;
        filter::AudioFilter* filter;

        std::function<void(State)> onStateChanged;
        std::function<void(float,float)> onProgressChanged;
        std::function<void(const std::string&)> onMediumChanged;
        std::function<void(unsigned)> onVolumeChanged;

        static AudioPlayer* instance;
    };
}