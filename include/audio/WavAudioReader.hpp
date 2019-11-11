#pragma once
#include <string>
#include <audio/WavAudioMetadata.hpp>
#include <filesystem/FileReadStream.hpp>

namespace audio {
    class WavAudioReader {
    public:
        explicit WavAudioReader(const std::string& file);
        [[nodiscard]] const std::string& getFilePath();
        [[nodiscard]] const WavAudioMetadata& getMetadata();
        [[nodiscard]] bool hasNext() const noexcept;
        [[nodiscard]] const std::vector<std::uint16_t>& readNext(std::size_t count);
    private:
        void readRiffChunk();
        void readFormatChunk();
        void readDataChunk();

        filesystem::FileReadStream readStream;
        WavAudioMetadata metadata;
        std::size_t remainingDataSize;
        std::vector<std::uint16_t> currentData;
    };
}