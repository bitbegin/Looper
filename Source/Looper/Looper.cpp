// Looper.cpp: 目标的源文件。
//

#include "Looper.h"
#include <memory>
#include <thread>
#include "HandlerCallBack.h"
#include "LooperManager.h"
#include "MessageQueue.h"

namespace LooperFrame {

    Looper::Looper():
        exiting_(false),
        exited_(false),
        exitSafely_(false),
        looping_(false) {
        msgQueue = std::make_shared<MessageQueue>();
    }
    Looper::~Looper() {
    }

    std::shared_ptr<Looper> Looper::Create() {
        return std::make_shared<Looper>();
    }

    void Looper::Prepare() {
        std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        std::shared_ptr<Looper> looper = Create();
        LooperManager::GetInstance().Register(tid, std::static_pointer_cast<LooperBase>(looper));
    }

    std::shared_ptr<Looper> Looper::MyLooper() {
        std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        auto looper = std::static_pointer_cast<Looper>(LooperManager::GetInstance().Get(tid));
        if (looper == nullptr) {
            //LOGE("Please invoke Looper::Prepare first");
        }
        return looper;
    }

    void Looper::Loop() {
        MyLooper()->LoopInternal();
    }
    size_t Looper::MyLooperId() {
        std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        return tid;
    }
    void Looper::Exit() {
        std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        LooperManager::GetInstance().UnRegister(tid);
    }
    void Looper::Quit(bool safely) {
        if (exiting_ || exited_) {
            return;
        }
        exitSafely_ = safely;
        exiting_ = true;
        msgQueue->Notify();
    }
    std::string Looper::Dump() {
        return msgQueue->Dump();
    }
    std::size_t Looper::Size() {
        return msgQueue->Size();
    }
    void Looper::PostMessage(std::shared_ptr<Message> msg) {
        if (exiting_ || exited_) {
            return;
        }
        msgQueue->PostMessage(msg);
    }
    std::shared_ptr<Message> Looper::PokeMessage() {
        return msgQueue->PokeMessage();
    }
    void Looper::RemoveMessage(std::int32_t what) {
        msgQueue->RemoteMessage(what);
    }
    void Looper::LoopInternal() {
        if (looping_ || exiting_ || exited_) {
            return;
        }
        looping_ = true;
        while (true) {
            std::shared_ptr<Message> msg = PokeMessage();
            if (msg != nullptr) {
                std::shared_ptr<HandlerCallBack> handler = msg->handler.lock();
                if (handler != nullptr) {
                    handler->ReceiveMessage(msg);
                }
            }
            if (exitSafely_) {
                if (exiting_ && msgQueue->Size() == 0) {
                    break;
                }
            } else if (exiting_) {
                break;
            }
        }
        msgQueue->Clear();
        exiting_ = false;
        exited_ = true;
        looping_ = false;
    }
}