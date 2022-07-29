#pragma once
#include <memory>

namespace LooperFrame {
    class Message;
    class HandlerCallBack {
    public:
        virtual void ReceiveMessage(std::shared_ptr<Message> msg) = 0;
    };
}