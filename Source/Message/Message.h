// Message.h: 目标的头文件。

#pragma once
#include <memory>
#include <cstdint>
#include "HandlerCallBack.h"

namespace LooperFrame {
    class Message {
    public:
        static std::shared_ptr<Message> Create(std::int32_t what_);
        ~Message();
        Message(std::int32_t what_);
    public:
        std::int32_t what;
        std::int32_t arg1;
        std::int32_t arg2;
        std::shared_ptr<void> obj;
    public:
        std::weak_ptr<HandlerCallBack> handler;
    };
}