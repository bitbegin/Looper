// Handler.cpp: 目标的源文件。
//

#include "Handler.h"

namespace LooperFrame {
    Handler::Handler(std::shared_ptr<Looper> looper, std::shared_ptr<HandlerCallBack> handlerCallBack) :
        looper_(looper),
        handlerCallBack_(handlerCallBack) {
    }
    Handler::~Handler() {
    }
    std::shared_ptr<Handler> Handler::Create(std::shared_ptr<Looper> looper, std::shared_ptr<HandlerCallBack> handlerCallBack) {
        return std::make_shared<Handler>(looper, handlerCallBack);
    }
    void Handler::Post(std::shared_ptr<Message> msg) {
        if (looper_ != nullptr) {
            msg->handler = handlerCallBack_;
            looper_->PostMessage(msg);
        }
    }
    void Handler::RemoveMessage(std::int32_t what) {
        if (looper_ != nullptr) {
            looper_->RemoveMessage(what);
        }
    }
    std::size_t Handler::Size() {
        if (looper_) {
            return looper_->Size();
        }
        return 0;
    }
}