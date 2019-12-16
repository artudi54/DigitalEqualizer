#include "PlaylistResponse.hpp"
#include <cstring>

namespace player_protocol::response {
    PlaylistResponse::PlaylistResponse()
        : files() {}

    PlaylistResponse::PlaylistResponse(const std::vector<std::string> &files)
        : files(files) {}

    MessageType PlaylistResponse::getMessageType() const {
        return MessageType::RESPONSE_PLAYLIST;
    }

    std::uint32_t PlaylistResponse::serialize(char *data) const {
        std::uint32_t offset = 0;

        std::uint32_t fileCount = static_cast<std::uint32_t>(files.size());
        std::memcpy(data + offset, &fileCount, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);

        for (auto& file : files) {
            std::uint32_t stringLength = static_cast<std::uint32_t>(file.size());

            std::memcpy(data + offset, &stringLength, sizeof(std::uint32_t));
            offset += sizeof(std::uint32_t);

            std::memcpy(data + offset, file.c_str(), stringLength);
            offset += stringLength;
        }

        return offset;
    }

    void PlaylistResponse::deserialize(const char *data) {
        std::uint32_t offset = 0;

        std::uint32_t fileCount;
        std::memcpy(&fileCount, data + offset, sizeof(std::uint32_t));
        offset += sizeof(std::uint32_t);
        files.resize(fileCount);

        for (auto& file : files) {
            std::uint32_t stringLength;
            std::memcpy(&stringLength, data + offset, sizeof(std::uint32_t));
            offset += sizeof(std::uint32_t);
            file.resize(stringLength);

            std::memcpy(file.data(), data + offset, stringLength);
            offset += stringLength;
        }
    }

    void PlaylistResponse::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    const std::vector<std::string> &PlaylistResponse::getFiles() const {
        return files;
    }

    void PlaylistResponse::setFiles(const std::vector<std::string> &files) {
        this->files = files;
    }
}