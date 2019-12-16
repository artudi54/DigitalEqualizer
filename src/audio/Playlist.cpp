#include "Playlist.hpp"
#include <string_view>
namespace audio {
    static bool isAudioFile(const std::string& fileName) {
        static constexpr std::string_view extension = ".wav";
        return fileName.size() > 4 && std::string_view(fileName).substr(fileName.size() - 4) == extension;
    }

    Playlist::Playlist(const std::string &path) {
        filesystem::DirectoryListing listing(path);
        for (std::size_t i = 0; i < listing.getFileCount(); ++i) {
            if (isAudioFile(listing.getFileNameAt(i))) {
                fileNames.push_back(listing.getFileNameAt(i));
                filePaths.push_back(listing.getFilePathAt(i));
            }
        }
    }

    const std::string& Playlist::getAudioFileNameAt(std::size_t idx) const {
        return fileNames[idx];
    }

    const std::string& Playlist::getAudioFilePathAt(std::size_t idx) const {
        return filePaths[idx];
    }

    const std::vector<std::string> &Playlist::getFileNames() const {
        return fileNames;
    }

    const std::vector<std::string> &Playlist::getFilePaths() const {
        return filePaths;
    }

    std::size_t Playlist::getAudioFileCount() const noexcept {
        return fileNames.size();
    }
}
