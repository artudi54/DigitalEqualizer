#pragma once
#include <complex>
#include <audio/filter/AudioFilter.hpp>

namespace audio::filter {
    class FFTAudioFilter  : public AudioFilter {
    protected:
        void processNormalizedSamples(std::vector<std::vector<float>>& samples) override;
        virtual void processFFT(std::vector<std::vector<std::complex<float>>>& fft) = 0;
    };
}
