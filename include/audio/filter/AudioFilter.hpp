#pragma once
#include <complex>
#include <cstdint>
#include <vector>
#include <audio/WavAudioMetadata.hpp>

namespace audio::filter {
    class AudioFilter {
    public:
        virtual ~AudioFilter();
        void process(std::vector<std::uint16_t>& samples, const WavAudioMetadata& metadata);

    protected:
        virtual void processNormalizedSamples(std::vector<std::complex<float>>& samples, std::size_t samplingRate) = 0;
    };
}
