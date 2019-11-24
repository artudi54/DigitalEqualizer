#pragma once
#include <complex>
#include <vector>

namespace math {
    std::vector<std::complex<float>> fft(std::vector<std::complex<float>> inputSequence);
    std::vector<std::complex<float>> ifft(std::vector<std::complex<float>> inputSequence);

    std::vector<std::complex<float>> fftReal(const std::vector<float>& inputSequence);
    std::vector<float> ifftReal(std::vector<std::complex<float>> inputSequence);
}
