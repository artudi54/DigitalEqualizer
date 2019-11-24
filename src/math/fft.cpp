#include "fft.hpp"
#include <algorithm>
#include <cmath>
using Complex = std::complex<float>;
using CArray= std::vector<Complex>;
namespace math {
    constexpr float PI = 3.1415926535897;

//    void fftRecursive(std::vector<std::complex<float>>& inputSequence) {
//        const std::size_t size = inputSequence.size();
//        if (size <= 1)
//            return;
//
//        std::vector<std::complex<float>> even(size / 2);
//        for (std::size_t i = 0; i < size; i+=2)
//            even[i / 2] = inputSequence[i];
//        std::vector<std::complex<float>> odd(size / 2);
//        for (std::size_t i = 1; i < size; i+=2)
//            odd[i / 2] = inputSequence[i];
//
//        fftRecursive(even);
//        fftRecursive(odd);
//
//        for (std::size_t i = 0; i < size / 2; ++i) {
//            std::complex<float> t = std::polar(1.0F, -2.0F * PI * i / static_cast<float>(size)) * odd[i];
//            inputSequence[i] = even[i] + t;
//            inputSequence[i + size / 2] = even[i] - t;
//        }
//    }

//     void fftRecursive(std::vector<std::complex<float>>& inputSequence) {
//
//        for (std::size_t i = 1; i < inputSequence.size() / 2; ++i)
//            std::swap(inputSequence[i], inputSequence[inputSequence.size() - i]);
//
//        for (std::size_t N = 2; N <= inputSequence.size(); N <<= 1u) {
//            for (std::size_t i = 0; i < inputSequence.size(); i += N) {
//                for (std::size_t k = 0; k < N / 2; k++) {
//
//                    std::size_t evenIndex = i + k;
//                    std::size_t oddIndex = i + k + (N / 2);
//                    std::complex<float> even = inputSequence[evenIndex];
//                    std::complex<float> odd = inputSequence[oddIndex];
//                    std::complex<float> exp = std::polar(1.0F, -2.0F * PI * static_cast<float>(i) / static_cast<float>(k)) * odd;
//
//                    inputSequence[evenIndex] = even + exp;
//                    inputSequence[oddIndex] = even - exp;
//                }
//            }
//        }
//    }

    void fftRecursive(CArray &x)
    {
        // DFT
        unsigned int N = x.size(), k = N, n;
        float thetaT = 3.14159265358979323846264338328F / static_cast<float>(N);
        Complex phiT = Complex(std::cos(thetaT), -std::sin(thetaT)), T;
        while (k > 1)
        {
            n = k;
            k >>= 1;
            phiT = phiT * phiT;
            T = 1.0L;
            for (unsigned int l = 0; l < k; l++)
            {
                for (unsigned int a = l; a < N; a += n)
                {
                    unsigned int b = a + k;
                    Complex t = x[a] - x[b];
                    x[a] += x[b];
                    x[b] = t * T;
                }
                T *= phiT;
            }
        }
        // Decimate
        unsigned int m = (unsigned int)log2(N);
        for (unsigned int a = 0; a < N; a++)
        {
            unsigned int b = a;
            // Reverse bits
            b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
            b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
            b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
            b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
            b = ((b >> 16) | (b << 16)) >> (32 - m);
            if (b > a)
            {
                Complex t = x[a];
                x[a] = x[b];
                x[b] = t;
            }
        }
        //// Normalize (This section make it not working correctly)
        //Complex f = 1.0 / sqrt(N);
        //for (unsigned int i = 0; i < N; i++)
        //	x[i] *= f;
    }

    std::vector<std::complex<float>> fft(std::vector<std::complex<float>> inputSequence) {
        fftRecursive(inputSequence);
        return inputSequence;
    }

    std::vector<std::complex<float>> ifft(std::vector<std::complex<float>> inputSequence) {
        auto conjugate = [](const std::complex<float>& comp) {
            return std::conj(comp);
        };
        auto divide = [&inputSequence] (const std::complex<float>& comp) {
            return comp / static_cast<float>(inputSequence.size());
        };

        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), conjugate);
        inputSequence = fft(std::move(inputSequence));
        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), conjugate);
        std::transform(inputSequence.begin(), inputSequence.end(), inputSequence.begin(), divide);
        return inputSequence;
    }

    std::vector<std::complex<float>> fftReal(const std::vector<float> &inputSequence) {
        std::vector<std::complex<float>> result(inputSequence.size());
        std::copy(inputSequence.begin(), inputSequence.end(), result.begin());
        return fft(std::move(result));
    }

    std::vector<float> ifftReal(std::vector<std::complex<float>> inputSequence) {
        inputSequence = ifft(std::move(inputSequence));
        std::vector<float> result(inputSequence.size());
        std::transform(inputSequence.begin(), inputSequence.end(), result.begin(), [](auto& comp) {return comp.real();});
        return result;
    }
}
