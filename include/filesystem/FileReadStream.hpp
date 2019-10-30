#pragma once
#include <cstddef>
#include <string>

namespace filesystem {
    class FileReadStream {
    public:
        explicit FileReadStream(const std::string& filePath);
        ~FileReadStream();

        [[nodiscard]] const std::string& getFilePath() const;

        void read(void* buffer, std::size_t count);
        void seek(std::size_t position);

    private:
        void* handle;
        std::string filePath;
    };
}

