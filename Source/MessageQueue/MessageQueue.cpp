// MessageQueue.cpp: 目标的源文件。
//

#include "MessageQueue.h"

namespace LooperFrame {
    const std::size_t QUEUE_MAX = 1024;

    MessageQueue::MessageQueue(): capacity(QUEUE_MAX) {
    }
    MessageQueue::MessageQueue(std::size_t cap):
        capacity(cap) {
    }
    MessageQueue::~MessageQueue() {
        Clear();
    }
    bool MessageQueue::PostMessage(std::shared_ptr<Message> msg) {
        std::unique_lock<std::mutex> lock(mutexQueue);
        if (queue.size() > capacity) {
            return false;
        }
        queue.push_back(msg);
        condQueue.notify_one();
        return true;
    }

    std::shared_ptr<Message> MessageQueue::PokeMessage() {
        std::unique_lock<std::mutex> lock(mutexQueue);
        if (queue.size() <= 0) {
            condQueue.wait(lock);
        }
        if (queue.empty()) {
            return nullptr;
        }
        std::shared_ptr<Message> msg = queue.front();
        queue.pop_front();
        return msg;
    }

    std::size_t MessageQueue::Size() {
        std::unique_lock<std::mutex> lock(mutexQueue);
        return queue.size();
    }
    bool MessageQueue::Empty() {
        std::unique_lock<std::mutex> lock(mutexQueue);
        return queue.empty();
    }
    void MessageQueue::Clear() {
        std::unique_lock<std::mutex> lock(mutexQueue);
        if (queue.empty()) {
            condQueue.notify_one();
            return;
        }
        queue.clear();
        condQueue.notify_one();
    }
    void MessageQueue::RemoteMessage(std::int32_t what) {
        std::unique_lock<std::mutex> lock(mutexQueue);
        auto it = queue.begin();
        while (it != queue.end()) {
            if (what == (*it)->what) {
                it = queue.erase(it);
                continue;
            }
            it++;
        }
    }
    void MessageQueue::Notify() {
        std::unique_lock<std::mutex> lock(mutexQueue);
        condQueue.notify_one();
    }
    std::string MessageQueue::Dump() {
        return "";
    }
}