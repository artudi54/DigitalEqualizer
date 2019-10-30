#pragma once
#include <string>
#include <audio/WavAudioMetadata.hpp>
#include <sys/FileReadStream.hpp>

namespace audio {
    class WavAudioReader {
    public:
        explicit WavAudioReader(const std::string& file);
        [[nodiscard]] const std::string& getFilePath();
        [[nodiscard]] const WavAudioMetadata& getMetadata();
        [[nodiscard]] bool hasNext() const noexcept;
        [[nodiscard]] const std::vector<std::uint16_t>& readNext();
    private:
        void readRiffChunk();
        void readFormatChunk();
        void readDataChunk();

        sys::FileReadStream readStream;
        WavAudioMetadata metadata;
        std::size_t remainingDataSize;
        std::vector<std::uint16_t> currentData;
    };
}