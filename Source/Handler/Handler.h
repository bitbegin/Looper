// Handler.h: 目标的头文件。

#pragma once
#include <memory>
#include <cstdint>
#include "HandlerCallBack.h"
#include "Looper.h"
#include "Message.h"

namespace LooperFrame {
    class Handler {
    public:
        Handler(std::shared_ptr<Looper> looper, std::shared_ptr<HandlerCallBack> handlerCallBack);
        ~Handler();
    public:
        static std::shared_ptr<Handler> Create(std::shared_ptr<Looper> looper, std::shared_ptr<HandlerCallBack> handlerCallBack);
        void Post(std::shared_ptr<Message> msg);
        void RemoveMessage(std::int32_t what);
        std::size_t Size();
    private:
        std::shared_ptr<Looper> looper_;
        std::shared_ptr<HandlerCallBack> handlerCallBack_;
    };
}