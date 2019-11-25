#pragma once
#include <audio/filter/FFTAudioFilter.hpp>

namespace audio::filter {
    class DigitalEqualizerParameters {
    public:
        enum class FrequenciesType {
            ISOOctave
        };
        DigitalEqualizerParameters() noexcept;

        void setFrequenciesType(FrequenciesType frequenciesType);

        [[nodiscard]] float getGainDb() const noexcept;
        void setGainDb(float gainDb) noexcept;
        [[nodiscard]] float getGain() const noexcept;

        [[nodiscard]] std::size_t getFilterCount() const noexcept;

        [[nodiscard]] float getFrequencyAt(std::size_t idx) const;

        [[nodiscard]] float getDbGain(std::size_t idx) const;
        void setDbGainAt(std::size_t idx, float dbGain);
        [[nodiscard]] float getGainAt(std::size_t idx) const;
        [[nodiscard]] float getGainAtFrequency(float frequency) const;

    private:
        class FilterNode {
        public:
            explicit FilterNode(float frequency, float dbGain = 0.0F);

            [[nodiscard]] float getFrequency() const;

            [[nodiscard]] float getGainDb() const;
            void setGainDb(float dbGain);
            [[nodiscard]] float getGain() const;

        private:
            float frequency;
            float gainDb;
            float gain;
        };

        float gainDb;
        float gain;
        std::vector<FilterNode> nodes;
    };


    class DigitalEqualizerFilter : public FFTAudioFilter {
    public:
        DigitalEqualizerFilter();

        [[nodiscard]] const DigitalEqualizerParameters &getParameters() const;
        void setParameters(const DigitalEqualizerParameters &parameters);

    protected:
        void processFFT(std::vector<std::complex<float>>& fft, std::size_t samplingRate) override;
    private:
        [[nodiscard]] float getFrequency(std::size_t i, std::size_t size, std::size_t samplingRate) const;

        DigitalEqualizerParameters parameters;
    };
}
