// Looper.h: 目标的头文件。

#pragma once
#include <memory>
#include <mutex>
#include <atomic>
#include <string>
#include "LooperBase.h"
#include "LooperManager.h"
#include "Message.h"
#include "MessageQueue.h"

namespace LooperFrame {
    class Looper : public LooperBase {
    public:
        Looper();
        ~Looper() override;
    public:
        static std::shared_ptr<Looper> Create();
        static void Prepare();
        static void Loop();
        static std::shared_ptr<Looper> MyLooper();
        static size_t MyLooperId();
        static void Exit();
        void Quit(bool safely);
        std::string Dump();
        std::size_t Size();
        void PostMessage(std::shared_ptr<Message> msg) override;
        std::shared_ptr<Message> PokeMessage();
        void RemoveMessage(std::int32_t what);
    private:
        void LoopInternal();
    private:
        std::atomic_bool exiting_;
        std::atomic_bool exited_;
        std::atomic_bool exitSafely_;
        std::atomic_bool looping_;
        std::shared_ptr<MessageQueue> msgQueue;
    };
}