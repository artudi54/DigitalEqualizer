#pragma once
#include <string>
#include <vector>
#include <player_protocol/Message.hpp>

namespace player_protocol::response {
    class PlaylistResponse : public Message {
    public:
        PlaylistResponse();

        explicit PlaylistResponse(const std::vector<std::string> &files);

        [[nodiscard]] MessageType getMessageType() const override;
        [[nodiscard]] std::uint32_t serialize(char *data) const override;
        void deserialize(const char *data) override;
        void visit(MessageVisitor &visitor) const override;

        [[nodiscard]] const std::vector<std::string> &getFiles() const;
        void setFiles(const std::vector<std::string> &files);

    private:
        std::vector<std::string> files;
    };
}