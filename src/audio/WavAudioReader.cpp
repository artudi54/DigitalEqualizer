#include "WavAudioReader.hpp"
#include <array>
#include <string>

namespace audio {
    namespace headers {
        using Header = std::array<char, 4>;
        constexpr Header RIFF =  {'R', 'I', 'F', 'F'};
        constexpr Header WAVE = {'W', 'A', 'V', 'E'};
        constexpr Header FORMAT = {'f', 'm', 't', ' '};
        constexpr Header DATA = {'d', 'a', 't', 'a'};
    }

    struct Chunk {
        headers::Header header;
        std::uint32_t size;
    };

    WavAudioReader::WavAudioReader(const std::string &file)
        : readStream(file)
        , metadata()
        , remainingDataSize(0)
        , currentData() {
        readRiffChunk();
        readFormatChunk();
        readDataChunk();
    }


    const std::string &WavAudioReader::getFilePath() {
        return readStream.getFilePath();
    }

    const WavAudioMetadata &WavAudioReader::getMetadata() {
        return metadata;
    }

    bool WavAudioReader::hasNext() const noexcept {
        return remainingDataSize != 0;
    }

    const std::vector<std::uint16_t>& WavAudioReader::readNext(std::size_t count) {
        if (!hasNext())
            throw std::runtime_error("No data to read remaining in '" + getFilePath() + "'");
        std::size_t readSize = remainingDataSize < count ? remainingDataSize : count;
        currentData.resize(readSize);
        readStream.read(currentData.data(), currentData.size());
        remainingDataSize -= readSize;
        return currentData;
    }

    void WavAudioReader::readRiffChunk() {
        Chunk riffChunk = {};
        headers::Header waveHeader = {};
        readStream.read(&riffChunk, sizeof(riffChunk));
        readStream.read(&waveHeader, sizeof(headers::Header));

        if (riffChunk.header != headers::RIFF)
            throw std::runtime_error("File '" + getFilePath() + "' is not a riff file");
        if (waveHeader != headers::WAVE)
            throw std::runtime_error("File '" + getFilePath() + "' is not a wave file");
    }

    void WavAudioReader::readFormatChunk() {
        Chunk formatSubChunk = {};
        readStream.read(&formatSubChunk, sizeof(formatSubChunk));

        if (formatSubChunk.header != headers::FORMAT)
            throw std::runtime_error("Filed to read format from '" + getFilePath() + "'");
        const std::size_t MIN_CHUNK_SIZE = 16;
        if (formatSubChunk.size < MIN_CHUNK_SIZE || formatSubChunk.size > sizeof(WavAudioMetadata))
            throw std::runtime_error("Filed to read invalid sized format from '" + getFilePath() + "'");


        readStream.read(&metadata, formatSubChunk.size);
        if (metadata.getFormatTag() != WavFormatTag::PCM)
            throw std::runtime_error("Non PCM file '" + getFilePath() + "' not supported");
        if (metadata.getChannelsNumber() > 2)
            throw std::runtime_error("Channel number greater than 2 in file '" + getFilePath() + "' not supported");
        const std::uint16_t SUPPORTED_SAMPLING = 48000;
        if (metadata.getSamplingRate() > SUPPORTED_SAMPLING)
            throw std::runtime_error("Unsupported " + std::to_string(SUPPORTED_SAMPLING) + " sampling in file '" + getFilePath() + "'");
    }

    void WavAudioReader::readDataChunk() {
        Chunk dataSubChunk = {};
        readStream.read(&dataSubChunk, sizeof(Chunk));
        if (dataSubChunk.header != headers::DATA)
            throw std::runtime_error("Failed to read data chunk from '" + getFilePath() + "'");
        remainingDataSize = dataSubChunk.size;
    }
}