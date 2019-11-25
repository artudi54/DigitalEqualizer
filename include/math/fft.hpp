#pragma once
#include <complex>
#include <vector>

namespace math {
    void fft(std::vector<std::complex<float>>& inputSequence);
    void ifft(std::vector<std::complex<float>>& inputSequence);
}
