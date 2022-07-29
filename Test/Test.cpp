// LoopeFrame.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <thread>
#include <chrono>
#include "Handler.h"
#include "HandlerThread.h"

using namespace std;

namespace LooperFrame {
    std::mutex g_mutexLog;
    std::shared_ptr<Handler> g_handler21;
    std::shared_ptr<Handler> g_handler22;
    class MyHandlerCallBack1 : public HandlerCallBack {
    public:
        void ReceiveMessage(std::shared_ptr<Message> msg) override {
            std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
            std::lock_guard<std::mutex> lock(g_mutexLog);
            cout << "tid: " << (uint16_t)tid << " cb1 what: " << msg->what << " arg1: " << msg->arg1 << endl;
        }
    };
    class MyHandlerCallBack2 : public HandlerCallBack {
    public:
        void ReceiveMessage(std::shared_ptr<Message> msg) override {
            std::size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
            std::lock_guard<std::mutex> lock(g_mutexLog);
            cout << "tid: " << (uint16_t)tid << " cb2 what: " << msg->what << " arg1: " << msg->arg1 << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            if (g_handler21) {
                auto msg21 = Message::Create(msg->what + 100);
                g_handler21->Post(msg21);
            }
        }
    };

    void test()
    {
        int count = 0;
        std::shared_ptr<HandlerThread> handlerThread1 = HandlerThread::Create("task1");
        std::shared_ptr<HandlerThread> handlerThread2 = HandlerThread::Create("task2");
        std::shared_ptr<Handler> handler11 = Handler::Create(handlerThread1->GetLooper(), std::make_shared<MyHandlerCallBack1>());
        std::shared_ptr<Handler> handler12 = Handler::Create(handlerThread1->GetLooper(), std::make_shared<MyHandlerCallBack2>());
        std::shared_ptr<Handler> handler21 = Handler::Create(handlerThread2->GetLooper(), std::make_shared<MyHandlerCallBack1>());
        std::shared_ptr<Handler> handler22 = Handler::Create(handlerThread2->GetLooper(), std::make_shared<MyHandlerCallBack2>());
        g_handler21 = handler21;
        g_handler22 = handler22;
        while (count++ < 10) {
            auto msg11 = Message::Create(count);
            msg11->arg1 = 11;
            auto msg12 = Message::Create(count + 100);
            msg12->arg1 = 12;
            handler11->Post(msg11);
            //handler12->Post(msg12);
            auto msg21 = Message::Create(count);
            msg21->arg1 = 21;
            auto msg22 = Message::Create(count + 100);
            msg22->arg1 = 22;
            handler21->Post(msg21);
            handler22->Post(msg22);
            //Sleep(1000);
        }
        handlerThread1->QuitSafely();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


int main()
{
    LooperFrame::test();
    cout << "finished." << endl;
    return 0;
}
