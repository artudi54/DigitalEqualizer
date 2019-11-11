#pragma once
#include <memory>
#include <string>
#include <audio/AudioPreprocessor.hpp>
#include <audio/WavAudioReader.hpp>
#include <sys/Task.hpp>

namespace audio {
    class AudioPlayer : public sys::Task {
        friend class Handlers;
    public:
        enum class State {
            NoSource,
            Stopped,
            Playing,
            Paused
        };

        AudioPlayer();
        ~AudioPlayer();
        void setSource(const std::string& sourcePath);
        void play();
        void pause();
        void stop();

        unsigned getVolume() const;
        void setVolume(unsigned volume);

        void setAudioPreprocessor(AudioPreprocessor& preprocessor);

        bool isEmpty();
        bool isPlaying();
        bool isPaused();
        bool isStopped();
        State getState() const;

    private:
        enum class BufferState {
            Done,
            Started,
            HalfWayThrough,
            Error
        };

        void progress() override;

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
        AudioPreprocessor* preprocessor;

        static AudioPlayer* instance;
    };
}