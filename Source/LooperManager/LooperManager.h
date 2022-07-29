// LooperManager.h: 目标的头文件。

#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <cstdint>
#include "LooperBase.h"

namespace LooperFrame {
    class LooperManager {
    public:
        static LooperManager& GetInstance();
    private:
        LooperManager();
        ~LooperManager();
    public:
        bool Register(std::size_t tid, std::shared_ptr<LooperBase> looper);
        std::shared_ptr<LooperBase> Get(std::size_t tid);
        void UnRegister(std::size_t tid);
        std::size_t Size();
    private:
        std::unordered_map<std::size_t, std::shared_ptr<LooperBase>> looperMap;
        std::mutex mutexMap;
    };
}