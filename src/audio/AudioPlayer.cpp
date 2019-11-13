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
        static void handleError() {
            AudioPlayer::instance->handleError();
        }
        static void handleBufferHalfWay() {
            AudioPlayer::instance->handleBufferHalfWay();
        }
        static void handleBufferDone() {
            AudioPlayer::instance->handleBufferDone();
        }
    };
}

extern "C" {
    void BSP_AUDIO_OUT_Error_CallBack(void) {
        audio::Handlers::handleError();
    }
    void BSP_AUDIO_OUT_HalfTransfer_CallBack(void) {
        audio::Handlers::handleBufferHalfWay();
    }
    void BSP_AUDIO_OUT_TransferComplete_CallBack() {
        audio::Handlers::handleBufferDone();
    }
}

namespace audio {
    const std::size_t BUFFER_SIZE = 4096;

    AudioPlayer::AudioPlayer()
        : state(State::NoSource)
        , bufferState(BufferState::Done)
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
        if (!isEmpty())
            playerDeinitialize();
        reader = std::make_unique<WavAudioReader>(sourcePath);
        state = State::Stopped;
    }

    void AudioPlayer::play() {
        validateNotEmpty();

        if (isPaused()) {
            playerUnpause();
            state = State::Playing;
            return;
        }
        if (isPlaying())
            return;
        playerInitialize();
        state = State::Playing;
    }

    void AudioPlayer::pause() {
        validateNotEmpty();

        if (isPaused()) {
            playerUnpause();
            state = State::Playing;
            return;
        }
        if (isStopped())
            return;
        playerPause();
        state = State::Paused;
    }

    void AudioPlayer::stop() {
        validateNotEmpty();
        if (isStopped())
            return;
        playerDeinitialize();
        state = State::Stopped;
    }

    unsigned AudioPlayer::getVolume() const {
        return volume;
    }

    void AudioPlayer::setVolume(unsigned volume) {
        if (volume > 100)
            throw std::invalid_argument("Volume cannot be greater than 100");
        this->volume = volume;
        if (state == State::Playing)
            playerSetVolume();
    }

    void AudioPlayer::setAudioFilter(filter::AudioFilter &filter) {
        this->filter = &filter;
    }

    bool AudioPlayer::isEmpty() const {
        return state == State::NoSource;
    }

    bool AudioPlayer::isPlaying() const {
        return state == State::Playing;
    }

    bool AudioPlayer::isPaused() const {
        return state == State::Paused;
    }

    bool AudioPlayer::isStopped() const {
        return state == State::Stopped;
    }

    AudioPlayer::State AudioPlayer::getState() const {
        return state;
    }

    void AudioPlayer::progress() {
        if (!isPlaying())
            return;
        if (bufferState == BufferState::Error)
            throw std::runtime_error("Error occurred while playing '" + reader->getFilePath() + "'");

        if (cachedBuffer.empty() && reader->hasNext()) {
            cachedBuffer = reader->readNext(BUFFER_SIZE);
            if (filter != nullptr)
                filter->process(cachedBuffer, reader->getMetadata());
        }

        if (bufferState == BufferState::Done) {
            std::swap(playingBuffer, cachedBuffer);
            if (playingBuffer.empty()) {
                bufferState = BufferState::Done;
                stop();
                return;
            }
            cachedBuffer.clear();
            playerPlayBuffer();
            bufferState = BufferState::Started;
        }
    }

    void AudioPlayer::playerInitialize() {
        if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, static_cast<std::uint8_t>(volume), reader->getMetadata().getSamplingRate()) != AUDIO_OK)
            throw std::runtime_error("Failed to playerInitialize audio player for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::playerDeinitialize() {
        if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_HW) != AUDIO_OK)
            throw std::runtime_error("Failed to stop audio player for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::playerPlayBuffer() {
        if (BSP_AUDIO_OUT_Play(playingBuffer.data(), playingBuffer.size()) != AUDIO_OK)
            throw std::runtime_error("Failed to play audio from '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::playerSetVolume() {
        if (BSP_AUDIO_OUT_SetVolume(static_cast<std::uint8_t>(volume)) != AUDIO_OK)
            throw std::runtime_error("Failed to play volume from '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::playerPause() {
        if (BSP_AUDIO_OUT_Pause() != AUDIO_OK)
            throw std::runtime_error("Failed to pause playing for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::playerUnpause() {
        if (BSP_AUDIO_OUT_Resume() != AUDIO_OK)
            throw std::runtime_error("Failed to unpause playing for '" + reader->getFilePath() + "'");
    }

    void AudioPlayer::handleError() {
        bufferState = BufferState::Error;
    }

    void AudioPlayer::handleBufferHalfWay() {
        bufferState = BufferState::HalfWayThrough;
    }

    void AudioPlayer::handleBufferDone() {
        bufferState = BufferState::Done;
    }

    void AudioPlayer::validateNotEmpty() {
        if (isEmpty())
            throw std::runtime_error("No audio source provided");
    }

    AudioPlayer* AudioPlayer::instance = nullptr;
}