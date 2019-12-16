#pragma once

namespace player_protocol {
    class Message;
    namespace changed {
        class MediumChangedMessage;
        class TimeChangedMessage;
        class VolumeChangedMessage;
    }
    namespace request {
        class ChangeMediumRequest;
        class ChangeVolumeRequest;
        class PauseRequest;
        class PlayRequest;
        class SeekRequest;
        class StopRequest;
    }
    namespace response {
        class ErrorResponse;
        class OkResponse;
    }

    class MessageVisitor {
    public:
        virtual ~MessageVisitor();
        virtual void handleMessage(const changed::MediumChangedMessage& message) = 0;
        virtual void handleMessage(const changed::TimeChangedMessage& message) = 0;
        virtual void handleMessage(const changed::VolumeChangedMessage& message) = 0;

        virtual void handleMessage(const request::ChangeMediumRequest& message) = 0;
        virtual void handleMessage(const request::ChangeVolumeRequest& message) = 0;
        virtual void handleMessage(const request::PauseRequest& message) = 0;
        virtual void handleMessage(const request::PlayRequest& message) = 0;
        virtual void handleMessage(const request::SeekRequest& message) = 0;
        virtual void handleMessage(const request::StopRequest& message) = 0;

        virtual void handleMessage(const response::ErrorResponse& message) = 0;
        virtual void handleMessage(const response::OkResponse& message) = 0;
    };

    class MessageClientVisitor : public MessageVisitor {
    public:
        void handleMessage(const request::ChangeMediumRequest& message) final;
        void handleMessage(const request::ChangeVolumeRequest& message) final;
        void handleMessage(const request::PauseRequest& message) final;
        void handleMessage(const request::PlayRequest& message) final;
        void handleMessage(const request::SeekRequest& message) final;
        void handleMessage(const request::StopRequest& message) final;
        virtual void handleInvalidMessage(const Message& message) = 0;
    };

    class MessageServerVisitor : public MessageVisitor {
    public:
        void handleMessage(const changed::MediumChangedMessage& message) final;
        void handleMessage(const changed::TimeChangedMessage& message) final;
        void handleMessage(const changed::VolumeChangedMessage& message) final;
        void handleMessage(const response::ErrorResponse& message) final;
        void handleMessage(const response::OkResponse& message) final;
        virtual void handleInvalidMessage(const Message& message) = 0;
    };
}
