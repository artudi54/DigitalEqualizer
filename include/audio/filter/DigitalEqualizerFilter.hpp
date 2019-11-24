#pragma once
#include <audio/filter/FFTAudioFilter.hpp>

namespace audio::filter {
    class DigitalEqualizerFilter : public FFTAudioFilter {
    public:
        DigitalEqualizerFilter();
    protected:
        void processFFT(std::vector<std::vector<std::complex<float>>>& fft) override;
    private:
        struct FilterNode {
        public:
            explicit FilterNode(float frequency, float dbGain = 0.0F);

            [[nodiscard]] float getFrequency() const;

            [[nodiscard]] float getDbGain() const;
            void setDbGain(float dbGain);

            [[nodiscard]] float getGain() const;

        private:
            float frequency;
            float dbGain;
            float gain;
        };

        float preampDb;
        float preamp;
        std::vector<FilterNode> nodes;
    };
}
