#pragma once
#include <cstdint>
#include <vector>

namespace audio {
    class AudioPreprocessor {
    public:
        virtual ~AudioPreprocessor();
        virtual void preprocess(std::vector<std::uint16_t>& samples) = 0;
    };
}
