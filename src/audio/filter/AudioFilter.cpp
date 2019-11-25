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
        static std::vector<std::vector<std::complex<float>>> normalizedSamples;

        std::size_t channelsNumber = metadata.getChannelsNumber();
        std::size_t samplesPerChannel = samples.size() / channelsNumber;
        std::size_t samplingRate = metadata.getSamplingRate();
        normalizedSamples.resize(channelsNumber);

        for (std::size_t i = 0; i < channelsNumber; ++i) {
            normalizedSamples[i].resize(samplesPerChannel);
            for (std::size_t j = 0; j < samplesPerChannel; ++j)
                normalizedSamples[i][j] = sampleToNormalized(samples[j * channelsNumber + i]);
        }

        for (auto& channelSamples: normalizedSamples)
            processNormalizedSamples(channelSamples, samplingRate);

        for (std::size_t i = 0; i < samples.size(); ++i)
            samples[i] = normalizedToSample(normalizedSamples[i % channelsNumber][i / channelsNumber].real());
    }
}