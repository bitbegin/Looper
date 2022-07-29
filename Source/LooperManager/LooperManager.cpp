// LooperManager.cpp: 目标的源文件。
//

#include "LooperManager.h"

namespace LooperFrame {
    LooperManager::LooperManager() {}
    LooperManager::~LooperManager() {}
    LooperManager& LooperManager::GetInstance() {
        static LooperManager instance;
        return instance;
    }
    bool LooperManager::Register(std::size_t tid, std::shared_ptr<LooperBase> looper) {
        std::lock_guard<std::mutex> lock(mutexMap);
        auto it = looperMap.find(tid);
        if (it == looperMap.end()) {
            looperMap[tid] = looper;
            return true;
        }
        return false;
    }
    std::shared_ptr<LooperBase> LooperManager::Get(std::size_t tid) {
        std::lock_guard<std::mutex> lock(mutexMap);
        auto it = looperMap.find(tid);
        if (it == looperMap.end()) {
            return nullptr;
        }
        return it->second;
    }
    void LooperManager::UnRegister(std::size_t tid) {
        std::lock_guard<std::mutex> lock(mutexMap);
        auto it = looperMap.find(tid);
        if (it != looperMap.end()) {
            looperMap.erase(it);
        }
    }
    std::size_t LooperManager::Size() {
        std::lock_guard<std::mutex> lock(mutexMap);
        return looperMap.size();
    }
}