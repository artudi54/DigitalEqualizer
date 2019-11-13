#pragma once
#include <cstdint>
#include <vector>
#include <audio/WavAudioMetadata.hpp>

namespace audio::filter {
    class AudioFilter {
    public:
        virtual ~AudioFilter();
        void process(std::vector<std::uint16_t>& samples, const WavAudioMetadata& metadata);

    protected:
        virtual void processNormalizedSamples(std::vector<std::vector<float>>& samples, const WavAudioMetadata& metadata) {};

    private:
        static float sampleToNormalized(std::uint16_t sample, std::size_t samplingRate);
        static float normalizedToSample(float normalized, std::size_t samplingRate);
    };
}
