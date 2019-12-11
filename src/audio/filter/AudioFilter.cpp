#include "AudioFilter.hpp"
#include <cmath>
#include <numeric>

namespace audio::filter {
    constexpr float sampleToNormalized(std::uint16_t sample) noexcept {
        return static_cast<float>(static_cast<std::int16_t>(sample)) / 32768.F;
    }

    constexpr float normalizedToSample(float normalized) noexcept {
        return static_cast<std::uint16_t>(static_cast<std::int16_t>(std::round(normalized * 32768.F)));
    }

    AudioFilter::~AudioFilter() = default;

    void AudioFilter::process(std::vector<std::uint16_t> &samples, const WavAudioMetadata &metadata) {
        constexpr std::size_t SPLIT = 4;
        static std::vector<std::vector<std::complex<float>>> normalizedSamples;

        for (std::size_t splitNum = 0, offset = 0; splitNum < SPLIT; ++splitNum, offset += samples.size() / SPLIT) {
            std::size_t channelsNumber = metadata.getChannelsNumber();
            std::size_t samplesPerChannel = samples.size() / channelsNumber;
            std::size_t samplingRate = metadata.getSamplingRate();
            normalizedSamples.resize(channelsNumber);

            for (std::size_t i = 0; i < channelsNumber; ++i) {
                normalizedSamples[i].resize(samplesPerChannel / SPLIT);
                for (std::size_t j = 0; j < samplesPerChannel / SPLIT; ++j)
                    normalizedSamples[i][j] = sampleToNormalized(samples[offset + j * channelsNumber + i]);
            }

            for (auto &channelSamples: normalizedSamples)
                processNormalizedSamples(channelSamples, samplingRate);

            for (std::size_t i = 0; i < samples.size() / SPLIT; ++i)
                samples[offset + i] = normalizedToSample(normalizedSamples[i % channelsNumber][i / channelsNumber].real());
        }
    }
}