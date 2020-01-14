#include "DigitalEqualizerFilter.hpp"
#include <cmath>
#include <algorithm>
volatile float sum = 15;
namespace audio::filter {
    static float dbToGain(float db) {
        return std::pow(10.0F, db / 20.0F);
    }



    DigitalEqualizerParameters::FilterNode::FilterNode(float frequency, float dbGain)
        : frequency(frequency)
        , gainDb(dbGain)
        , gain(dbToGain(dbGain)) {}

    float DigitalEqualizerParameters::FilterNode::getFrequency() const {
        return frequency;
    }

    float DigitalEqualizerParameters::FilterNode::getGainDb() const {
        return gainDb;
    }

    void DigitalEqualizerParameters::FilterNode::setGainDb(float dbGain) {
        this->gainDb = dbGain;
        this->gain = dbToGain(dbGain);
    }

    float DigitalEqualizerParameters::FilterNode::getGain() const {
        return gain;
    }



    DigitalEqualizerParameters::DigitalEqualizerParameters() noexcept
        : gainDb(0.0F)
        , gain(dbToGain(gainDb))
        , nodes() {}

    void DigitalEqualizerParameters::setFrequenciesType(FrequenciesType frequenciesType) {
        nodes.clear();
        if (frequenciesType == FrequenciesType::ISOOctave) {
            nodes.emplace_back(31.5);
            nodes.emplace_back(63);
            nodes.emplace_back(125);
            nodes.emplace_back(250);
            nodes.emplace_back(500);
            nodes.emplace_back(1000);
            nodes.emplace_back(2000);
            nodes.emplace_back(4000);
            nodes.emplace_back(8000);
            nodes.emplace_back(16000);
        }
    }

    void DigitalEqualizerParameters::setGainDb(float gainDb) noexcept {
        this->gainDb = gainDb;
        gain = dbToGain(gainDb);
    }

    float DigitalEqualizerParameters::getGainDb() const noexcept {
        return gainDb;
    }

    float DigitalEqualizerParameters::getGain() const noexcept {
        return gain;
    }

    std::size_t DigitalEqualizerParameters::getFilterCount() const noexcept {
        return nodes.size();
    }

    float DigitalEqualizerParameters::getFrequencyAt(std::size_t idx) const {
        return nodes.at(idx).getFrequency();
    }

    float DigitalEqualizerParameters::getDbGain(std::size_t idx) const {
        return nodes.at(idx).getGainDb();
    }

    void DigitalEqualizerParameters::setDbGainAt(std::size_t idx, float dbGain) {
        return nodes.at(idx).setGainDb(dbGain);
    }

    float DigitalEqualizerParameters::getGainAt(std::size_t idx) const {
        return nodes.at(idx).getGain();
    }

    float DigitalEqualizerParameters::getGainAtFrequency(float frequency) const {
        auto freqComparator = [](auto& lhs, auto& rhs) {
            return lhs.getFrequency() < rhs.getFrequency();
        };
        auto upperIt = std::lower_bound(nodes.begin(), nodes.end(), FilterNode(frequency), freqComparator);
        auto lowerIt = upperIt == nodes.begin()? upperIt : std::prev(upperIt);
        if (lowerIt == upperIt)
            return lowerIt->getGain();
        float lowerFrequency = lowerIt != nodes.end()? lowerIt->getFrequency() : 0.0F;
        float lowerGain = lowerIt != nodes.end()? lowerIt->getGain() : 0.0F;
        float upperFrequency = upperIt != nodes.end()? upperIt->getFrequency() : 20000.0F;
        float upperGain = upperIt != nodes.end()? upperIt->getGain() : 0.0F;
        float m = (upperGain - lowerGain) / (upperFrequency -  lowerFrequency);
        float b = lowerGain - m * lowerFrequency;
        return m * frequency + b;
    }


    DigitalEqualizerFilter::DigitalEqualizerFilter()
        : parameters() {}

    const DigitalEqualizerParameters &DigitalEqualizerFilter::getParameters() const {
        return parameters;
    }

    void DigitalEqualizerFilter::setParameters(const DigitalEqualizerParameters &parameters) {
        this->parameters = parameters;
    }

    void DigitalEqualizerFilter::processFFT(std::vector<std::complex<float>> &fft, std::size_t samplingRate) {
        for (std::size_t i = 1; i < fft.size(); ++i) {
            float frequency = getFrequency(i, fft.size(), samplingRate);
            fft[i] = std::polar(std::abs(fft[i]) * parameters.getGain() * parameters.getGainAtFrequency(frequency), std::arg(fft[i]));
        }
        sum = 0.0F;
        for (std::size_t i = 0; i <= fft.size() / 2; ++i)
            sum += std::abs(fft[i]);
        sum /= fft.size();
    }

    float DigitalEqualizerFilter::getFrequency(std::size_t i, std::size_t size, std::size_t samplingRate) const {
        if (i >= size / 2)
            i = size - i;
        return static_cast<float>(i) * static_cast<float>(samplingRate) / (2.0F * static_cast<float>(size));
    }
}