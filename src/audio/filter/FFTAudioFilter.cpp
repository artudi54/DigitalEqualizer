#include "FFTAudioFilter.hpp"
#include <math/fft.hpp>

namespace audio::filter {
    void FFTAudioFilter::processNormalizedSamples(std::vector<std::complex<float>> &samples, std::size_t samplingRate) {
        math::fft(samples);
        for (auto& sample : samples)
            sample /= static_cast<float>(samples.size()) / 2.0F;

        processFFT(samples, samplingRate);

        math::ifft(samples);
        for (auto& sample : samples)
            sample *= static_cast<float>(samples.size()) / 2.0F;
    }
}
