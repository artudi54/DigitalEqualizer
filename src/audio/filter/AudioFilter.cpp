#include "AudioFilter.hpp"
#include <cmath>
#include <numeric>

namespace audio::filter {
    AudioFilter::~AudioFilter() = default;

    void AudioFilter::process(std::vector<std::uint16_t> &samples, const WavAudioMetadata &metadata) {
        std::size_t channelsNumber = metadata.getChannelsNumber();
        std::size_t samplesPerChannel = samples.size() / channelsNumber;
        std::size_t channelSamplingRate = metadata.getSamplingRate() / channelsNumber;

        std::vector<std::vector<float>> normalizedSamples(channelsNumber);

        for (std::size_t i = 0; i < channelsNumber; ++i) {
            normalizedSamples[i].resize(samplesPerChannel);
            for (std::size_t j = 0; j < samplesPerChannel; ++j) {
                float normalizedSample = sampleToNormalized(samples[j * channelsNumber + i],
                                                            channelSamplingRate);
                normalizedSamples[i][j] = normalizedSample;
            }
        }

        processNormalizedSamples(normalizedSamples);

        for (std::size_t i = 0; i < samples.size(); ++i) {
            std::uint16_t sample = normalizedToSample(normalizedSamples[i % channelsNumber][i / channelsNumber],
                                                      channelSamplingRate);
            samples[i] = sample;
        }
    }

    float AudioFilter::sampleToNormalized(std::uint16_t sample, std::size_t samplingRate) {
        return static_cast<float>(reinterpret_cast<std::int16_t&>(sample)) / static_cast<float>(samplingRate);
    }

    float AudioFilter::normalizedToSample(float normalized, std::size_t samplingRate) {
        return static_cast<std::uint16_t>(static_cast<std::int16_t>(std::round(normalized * samplingRate)));
    }
}