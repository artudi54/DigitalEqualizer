#include "fft.hpp"
#include <algorithm>
#include <cmath>

namespace math {
    constexpr float PI = 3.1415926535897;

    void fft(std::vector<std::complex<float>>& inputSequence) {
        // DFT
        unsigned int N = inputSequence.size(), k = N, n;
        float thetaT = PI / static_cast<float>(N);
        std::complex<float> phiT(std::cos(thetaT), -std::sin(thetaT)), T;
        while (k > 1)
        {
            n = k;
            k >>= 1;
            phiT = phiT * phiT;
            T = 1.0L;
            for (unsigned int l = 0; l < k; l++){
                for (unsigned int a = l; a < N; a += n){
                    unsigned int b = a + k;
                    std::complex<float> t = inputSequence[a] - inputSequence[b];
                    inputSequence[a] += inputSequence[b];
                    inputSequence[b] = t * T;
                }
                T *= phiT;
            }
        }
        // Decimate
        unsigned int m = (unsigned int)log2(N);
        for (unsigned int a = 0; a < N; a++){
            unsigned int b = a;
            // Reverse bits
            b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
            b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
            b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
            b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
            b = ((b >> 16) | (b << 16)) >> (32 - m);
            if (b > a) {
                std::swap(inputSequence[a], inputSequence[b]);
            }
        }
    }

    void ifft(std::vector<std::complex<float>>& inputSequence) {
        auto conjugate = [](const std::complex<float>& comp) {
            return std::conj(comp);
        };
        auto divide = [&inputSequence] (const std::complex<float>& comp) {
            return comp / static_cast<float>(inputSequence.size());
        };

        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), conjugate);
        fft(inputSequence);
        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), conjugate);
        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), divide);
    }
}
