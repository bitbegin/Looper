// HandlerThread.h: 目标的头文件。

#pragma once
#include <thread>
#include <cstdint>
#include <string>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Looper.h"

namespace LooperFrame {
    class HandlerThread {
    public:
        HandlerThread(const std::string& name);
        ~HandlerThread();
    public:
        static std::shared_ptr<HandlerThread> Create(const std::string &name);
        void RunInternal();
        void Quit();
        bool QuitSafely();
        std::shared_ptr<Looper> GetLooper();
    private:
        std::string name_;
        std::atomic_bool exiting_;
        std::atomic_bool exited_;
        std::thread thread_;
        std::shared_ptr<Looper> looper_;
        std::mutex mutexLooper;
        std::condition_variable condLooper;
    };
}