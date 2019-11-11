#include "AudioPlayer.hpp"
#include <stm32f4_discovery_audio.h>

// DMA handlers
extern "C" {
    extern I2S_HandleTypeDef hAudioOutI2s;
    void I2S3_IRQHandler(void) {
        HAL_DMA_IRQHandler(hAudioOutI2s.hdmatx);
    }
    void DMA2_Stream3_IRQHandler(void) {
        HAL_DMA_IRQHandler(hAudioOutI2s.hdmatx);
    }
}

namespace audio {
    class Handlers {
    public:
        static void errorHandler() {
            AudioPlayer::instance->errorHandler();
        }
        static void halfWayBufferHandler() {
            AudioPlayer::instance->halfWayBufferHandler();
        }
        static void bufferDoneHandler() {
            AudioPlayer::instance->bufferDoneHandler();
        }
    };
}

extern "C" {
    void BSP_AUDIO_OUT_Error_CallBack(void) {
        audio::Handlers::errorHandler();
    }
    void BSP_AUDIO_OUT_HalfTransfer_CallBack(void) {
        audio::Handlers::halfWayBufferHandler();
    }
    void BSP_AUDIO_OUT_TransferComplete_CallBack() {
        audio::Handlers::bufferDoneHandler();
    }
}

namespace audio {
    const std::size_t BUFFER_SIZE = 8192;

    AudioPlayer::AudioPlayer()
        : state(State::NoSource)
        , bufferState(BufferState::None)
        , error(false)
        , volume(100)
        , reader()
        , playingBuffer()
        , cachedBuffer() {
        if (instance != nullptr)
            throw std::runtime_error("Audio player instance already exists");
        instance = this;
    }
    AudioPlayer::~AudioPlayer() {
        if (state!= State::NoSource)
            stop();
        instance = nullptr;
    }

    void AudioPlayer::setSource(const std::string &sourcePath) {
        if (state != State::NoSource)
            deinitialize();
        reader = std::make_unique<WavAudioReader>(sourcePath);
        state = State::Stopped;
    }

    void AudioPlayer::play() {
        validateNotEmpty();
        if (state == State::Playing)
            return;
        initialize();
        state = State::Playing;
        progress();
    }

    void AudioPlayer::stop() {
        validateNotEmpty();
        if (state == State::Stopped)
            return;
        deinitialize();
        state = State::Stopped;
    }

    AudioPlayer::State AudioPlayer::getState() const {
        return state;
    }

    void AudioPlayer::progress() {
        if (state != State::Playing)
            return;
        if (error)
            throw std::runtime_error("Error occurred while playing '" + reader->getFilePath() + "'");

        if (bufferState == BufferState::None) {
            playingBuffer = reader->readNext(BUFFER_SIZE);
            if (BSP_AUDIO_OUT_Play(playingBuffer.data(), playingBuffer.size()) != AUDIO_OK)
                throw std::runtime_error("Failed to play audio from '" + reader->getFilePath() + "'");
            bufferState = BufferState::Started;
        }
        if (cachedBuffer.empty()) {
            if (!reader->hasNext()) {
                bufferState = BufferState::None;
                stop();
                return;
            }
            cachedBuffer = reader->readNext(BUFFER_SIZE);
        }
        if (bufferState == BufferState::Done) {
            std::swap(playingBuffer, cachedBuffer);
            cachedBuffer.clear();
            if (BSP_AUDIO_OUT_Play(playingBuffer.data(), playingBuffer.size()) != AUDIO_OK)
                throw std::runtime_error("Failed to play audio from '" + reader->getFilePath() + "'");
            bufferState = BufferState::Started;
        }

    }

    void AudioPlayer::initialize() {
        if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, static_cast<std::uint8_t>(volume * 0.8), reader->getMetadata().getSamplingRate()) != AUDIO_OK)
            throw std::runtime_error("Failed to initialize audio player for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::deinitialize() {
        if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW) != AUDIO_OK)
            throw std::runtime_error("Failed to stop audio player for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::errorHandler() {
        error = true;
    }

    void AudioPlayer::halfWayBufferHandler() {
        bufferState = BufferState::HalfWayThrough;
    }

    void AudioPlayer::bufferDoneHandler() {
        bufferState = BufferState::Done;
    }

    void AudioPlayer::validateNotEmpty() {
        if (state == State::NoSource)
            throw std::runtime_error("No audio source provided");
    }

    AudioPlayer* AudioPlayer::instance = nullptr;
}