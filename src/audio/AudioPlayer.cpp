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
    const std::size_t BUFFER_SIZE = 16384;

    AudioPlayer::AudioPlayer()
        : state(State::NO_SOURCE)
        , bufferState(BufferState::Done)
        , volume(100)
        , reader()
        , playingBuffer()
        , cachedBuffer()
        , filter(nullptr) {
        if (instance != nullptr)
            throw std::runtime_error("Audio player instance already exists");
        instance = this;
    }

    AudioPlayer::~AudioPlayer() {
        if (state != State::NO_SOURCE)
            stop();
        instance = nullptr;
    }

    void AudioPlayer::setSource(const std::string &sourcePath) {
        if (reader != nullptr && sourcePath == reader->getFilePath())
            return;
        bool wasPlaying = isPlaying();
        if (isPlaying() || isPaused())
            playerDeinitialize();
        reader = std::make_unique<WavAudioReader>(sourcePath);
        updateState(State::STOPPED);

        if (onMediumChanged != nullptr)
            onMediumChanged(sourcePath);
        if (onProgressChanged != nullptr)
            onProgressChanged(getCurrentTime(), getEndTime());
        if (wasPlaying)
            play();
    }

    void AudioPlayer::unloadSource() {
        stop();
        updateState(State::NO_SOURCE);
        if (onMediumChanged != nullptr)
            onMediumChanged("");
    }

    void AudioPlayer::play() {
        validateNotEmpty();

        if (isPaused()) {
            playerUnpause();
            updateState(State::PLAYING);
            return;
        }
        if (isPlaying())
            return;
        playerInitialize();
        updateState(State::PLAYING);
    }

    void AudioPlayer::pause() {
        validateNotEmpty();

        if (isPaused()) {
            playerUnpause();
            updateState(State::PLAYING);
            return;
        }
        if (isStopped())
            return;
        playerPause();
        updateState(State::PAUSED);
    }

    void AudioPlayer::stop() {
        validateNotEmpty();
        if (isStopped())
            return;
        playerDeinitialize();
        updateState(State::STOPPED);
        bufferState = BufferState::Done;
        seek(0.0F);
    }

    void AudioPlayer::seek(float time) {
        if (time > getEndTime())
            throw std::runtime_error("Invalid time value - greater than maximal time : (" + std::to_string(time) + "/" + std::to_string(getEndTime()) + ")");
        float progressRatio = time / getEndTime();
        auto position = static_cast<std::size_t>(progressRatio * reader->getTotalDataSize());
        reader->seek(position);
        if (onProgressChanged != nullptr)
            onProgressChanged(getCurrentTime(), getEndTime());
    }

    unsigned AudioPlayer::getVolume() const {
        return volume;
    }

    void AudioPlayer::setVolume(unsigned volume) {
        if (this->volume == volume)
            return;
        if (volume > 100)
            throw std::invalid_argument("Volume cannot be greater than 100");

        this->volume = volume;
        if (state == State::PLAYING)
            playerSetVolume();

        if (onVolumeChanged != nullptr)
            onVolumeChanged(getVolume());
    }

    void AudioPlayer::setAudioFilter(filter::AudioFilter &filter) {
        this->filter = &filter;
    }

    bool AudioPlayer::isEmpty() const {
        return state == State::NO_SOURCE;
    }

    bool AudioPlayer::isPlaying() const {
        return state == State::PLAYING;
    }

    bool AudioPlayer::isPaused() const {
        return state == State::PAUSED;
    }

    bool AudioPlayer::isStopped() const {
        return state == State::STOPPED;
    }

    AudioPlayer::State AudioPlayer::getState() const {
        return state;
    }

    float AudioPlayer::getCurrentTime() const {
        return static_cast<float>(reader->getReadDataSize())
               / static_cast<float>(reader->getMetadata().getChannelsNumber())
               / static_cast<float>(reader->getMetadata().getSamplingRate())
               / std::round(static_cast<float>(reader->getMetadata().getBitsPerSample()) / 8.0F);
    }

    float AudioPlayer::getEndTime() const {
        return static_cast<float>(reader->getTotalDataSize())
               / static_cast<float>(reader->getMetadata().getChannelsNumber())
               / static_cast<float>(reader->getMetadata().getSamplingRate())
               / std::round(static_cast<float>(reader->getMetadata().getBitsPerSample()) / 8.0F);
    }

    void AudioPlayer::setOnStateChanged(const std::function<void(State)> &onStateChanged) {
        this->onStateChanged = onStateChanged;
    }

    void AudioPlayer::setOnProgressChanged(const std::function<void(float, float)> &onProgressChanged) {
        this->onProgressChanged = onProgressChanged;
    }

    void AudioPlayer::setOnMediumChanged(const std::function<void(const std::string &)> &onMediumChanged) {
        this->onMediumChanged = onMediumChanged;
    }

    void AudioPlayer::setOnVolumeChanged(const std::function<void(unsigned)> &onVolumeChanged) {
        this->onVolumeChanged = onVolumeChanged;
    }

    void AudioPlayer::progress() {
        if (!isPlaying())
            return;
        if (bufferState == BufferState::Error)
            throw std::runtime_error("Error occurred while playing '" + reader->getFilePath() + "'");

        if (cachedBuffer.empty() && reader->hasNext()) {
            reader->readNext(cachedBuffer, BUFFER_SIZE);
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
            if (onProgressChanged != nullptr)
                onProgressChanged(getCurrentTime(), getEndTime());
        }
    }

    void AudioPlayer::playerInitialize() {
        if (BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_AUTO, static_cast<std::uint8_t>(volume),
                               reader->getMetadata().getSamplingRate()) != AUDIO_OK)
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

    AudioPlayer *AudioPlayer::instance = nullptr;

    void AudioPlayer::updateState(AudioPlayer::State state) {
        if (state == this->state)
            return;
        this->state = state;
        if (onStateChanged != nullptr)
            onStateChanged(this->state);
    }
}
