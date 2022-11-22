//
// Created by rrrr on 22-11-22.
//
#include "EventLoop.h"
#include <iostream>
namespace EvtHandle {
__thread EventLoop* t_loopInThisThread = 0;


EventLoop::EventLoop() :isLooping_(false), threadId_(pthread_self()) {
    std::cout<< "EventLoop created " << this << " in thread " << threadId_<<std::endl;
    if(t_loopInThisThread) {
        std::cout << "Another EventLoop " << t_loopInThisThread
        << " exists in this thread " << threadId_<<std::endl;
    } else {
        t_loopInThisThread = this;
    }
}

EventLoop::~EventLoop() {
    t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
    isLooping_ = true;
    ///todo : poll

    std::cout<< "EventLoop " << this << " start looping" << std::endl;
    isLooping_ = false;
}
}