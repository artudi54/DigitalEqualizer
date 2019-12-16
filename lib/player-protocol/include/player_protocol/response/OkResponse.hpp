#pragma once
#include <player_protocol/Message.hpp>

namespace player_protocol::response {
    class OkResponse : public EmptyMessage {
    public:
        [[nodiscard]] MessageType getMessageType() const override;
        void visit(MessageVisitor& visitor) const override;
    };
}
