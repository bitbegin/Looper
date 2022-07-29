// MessageQueue.h: 目标的头文件。

#pragma once
#include <mutex>
#include <list>
#include <condition_variable>
#include <memory>
#include <string>
#include <cstdint>
#include "Message.h"

namespace LooperFrame {
    class MessageQueue {
    public:
        MessageQueue();
        MessageQueue(std::size_t cap);
        ~MessageQueue();
        bool PostMessage(std::shared_ptr<Message> msg);
        std::shared_ptr<Message> PokeMessage();
        std::size_t Size();
        bool Empty();
        void Clear();
        void RemoteMessage(std::int32_t what);
        void Notify();
        std::string Dump();
    private:
        std::size_t capacity;
        std::mutex mutexQueue;
        std::condition_variable condQueue;
        std::list<std::shared_ptr<Message>> queue;
    };
}