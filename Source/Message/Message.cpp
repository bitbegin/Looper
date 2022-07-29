// Message.cpp: 目标的源文件。
//

#include "Message.h"

namespace LooperFrame {
    Message::Message(std::int32_t what_):
        what(what_), 
        arg1(-1),
        arg2(-1),
        obj(nullptr) {
    }
    Message::~Message(){
    }
    std::shared_ptr<Message> Message::Create(std::int32_t what_) {
        return std::make_shared<Message>(what_);
    }
}
