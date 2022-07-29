#pragma once
#include <memory>
#include "Message.h"

namespace LooperFrame {
    class LooperBase {
    public:
        virtual ~LooperBase() {};
        virtual void PostMessage(std::shared_ptr<Message> msg) = 0;
    };
}