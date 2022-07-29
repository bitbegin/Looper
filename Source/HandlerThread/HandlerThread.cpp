// HandlerThread.cpp: 目标的源文件。
//

#include "HandlerThread.h"
#include <string>
#include <thread>

namespace LooperFrame {
    HandlerThread::HandlerThread(const std::string& name):
        name_(name),
        looper_(nullptr),
        exiting_(false),
        exited_(false) {
        std::thread thd([this](HandlerThread *this_) {this_->RunInternal(); }, this);
        thread_.swap(thd);
    }
    HandlerThread::~HandlerThread() {
        if (looper_) {
            looper_->Quit(true);
        }
        if (thread_.joinable()) {
            thread_.join();
        }
        looper_ = nullptr;
    }
    std::shared_ptr<HandlerThread> HandlerThread::Create(const std::string& name) {
        return std::make_shared<HandlerThread>(name);
    }

    void HandlerThread::RunInternal() {
        exiting_ = false;
        exited_ = false;
        Looper::Prepare();
        {
            std::unique_lock<std::mutex> lock(mutexLooper);
            looper_ = Looper::MyLooper();
            condLooper.notify_one();
        }
        Looper::Loop();
        Looper::Exit();
        exiting_ = false;
        looper_ = nullptr;
        exited_ = true;
    }
    void HandlerThread::Quit() {
        if (exiting_ || exited_) {
            return;
        }
        exiting_ = true;
        auto looper = GetLooper();
        if (looper != nullptr) {
            looper->Quit(false);
        }
    }
    bool HandlerThread::QuitSafely() {
        if (exiting_ || exited_) {
            return false;
        }
        exiting_ = true;
        auto looper = GetLooper();
        if (looper != nullptr) {
            looper->Quit(true);
            return true;
        }
        return false;
    }
    std::shared_ptr<Looper> HandlerThread::GetLooper() {
        if (exited_) {
            return nullptr;
        }
        std::unique_lock<std::mutex> lock(mutexLooper);
        if (looper_ == nullptr) {
            condLooper.wait(lock);
        }
        return looper_;
    }
}