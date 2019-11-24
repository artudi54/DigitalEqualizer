#include "DigitalEqualizerFilter.hpp"
#include <cmath>

namespace audio::filter {
    static float dbToGain(float db) {
        return std::pow(10.0F, db / 20.0F);
    }

    DigitalEqualizerFilter::FilterNode::FilterNode(float frequency, float dbGain)
        : frequency(frequency)
        , dbGain(dbGain)
        , gain(dbToGain(dbGain)){}

    float DigitalEqualizerFilter::FilterNode::getFrequency() const {
        return frequency;
    }

    float DigitalEqualizerFilter::FilterNode::getDbGain() const {
        return dbGain;
    }

    void DigitalEqualizerFilter::FilterNode::setDbGain(float dbGain) {
        this->dbGain = dbGain;
        this->gain = dbToGain(dbGain);
    }

    float DigitalEqualizerFilter::FilterNode::getGain() const {
        return gain;
    }

    DigitalEqualizerFilter::DigitalEqualizerFilter()
        : preampDb(0)
        , preamp(dbToGain(preampDb))
        , nodes(){
        nodes.emplace_back(32, 1);
        nodes.emplace_back(64, 1);
        nodes.emplace_back(125, 1);
        nodes.emplace_back(250, 1);
        nodes.emplace_back(500, 1);
        nodes.emplace_back(1000, 1);
        nodes.emplace_back(2000, 1);
        nodes.emplace_back(4000, 1);
        nodes.emplace_back(8000, 1);
        nodes.emplace_back(16000, 1);
    }

    void DigitalEqualizerFilter::processFFT(std::vector<std::vector<std::complex<float>>> &fft) {
        for (auto & stream : fft)
            for (auto& sample : stream)
                sample *= preamp;
    }
}