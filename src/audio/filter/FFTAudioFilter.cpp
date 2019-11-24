#include "FFTAudioFilter.hpp"
#include <math/fft.hpp>

namespace audio::filter {
    void FFTAudioFilter::processNormalizedSamples(std::vector<std::vector<float>> &samples) {
        std::size_t channelCount = samples.size();
        std::vector<std::vector<std::complex<float>>> fft(samples.size());
        for (size_t i = 0; i < channelCount; ++i)
            fft[i] = math::fftReal(samples[i]);
        processFFT(fft);
        for (std::size_t i = 0; i < channelCount; ++i)
            samples[i] = math::ifftReal(fft[i]);
    }
}
