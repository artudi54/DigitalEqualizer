#pragma once
#include <complex>
#include <audio/filter/AudioFilter.hpp>

namespace audio::filter {
    class FFTAudioFilter  : public AudioFilter {
    protected:
        void processNormalizedSamples(std::vector<std::complex<float>>& samples, std::size_t samplingRate) override;
        virtual void processFFT(std::vector<std::complex<float>>& fft, std::size_t samplingRate) = 0;
    };
}
