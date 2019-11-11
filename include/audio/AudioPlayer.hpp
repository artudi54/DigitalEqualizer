#pragma once
#include <memory>
#include <string>
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
        };

        AudioPlayer();
        ~AudioPlayer();
        void setSource(const std::string& sourcePath);
        void play();
        void stop();
        State getState() const;

    private:
        enum class BufferState {
            None,
            Started,
            HalfWayThrough,
            Done
        };

        void progress() override;

        void initialize();
        void deinitialize();


        void errorHandler();
        void halfWayBufferHandler();
        void bufferDoneHandler();

        void validateNotEmpty();

        State state;
        BufferState bufferState;
        bool error;
        unsigned volume;
        std::unique_ptr<WavAudioReader> reader;
        std::vector<std::uint16_t> playingBuffer;
        std::vector<std::uint16_t> cachedBuffer;

        static AudioPlayer* instance;
    };
}