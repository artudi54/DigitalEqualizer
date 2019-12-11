#pragma once
#include <filesystem/DirectoryListing.hpp>

namespace audio {
    class Playlist {
    public:
        explicit Playlist(const std::string& path);
        [[nodiscard]] const std::string& getAudioFileNameAt(std::size_t idx) const;
        [[nodiscard]] const std::string& getAudioFilePathAt(std::size_t idx) const;
        [[nodiscard]] std::size_t getAudioFileCount() const noexcept;
    private:
        std::vector<std::string> fileNames;
        std::vector<std::string> filePaths;
    };
}