//
// Created by rrrr on 22-11-22.
//
#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"
#include <iostream>
namespace EvtHandle {
__thread EventLoop* t_loopInThisThread = 0;
const int kPollTimeMs = 10000;


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
    if(isLooping_) {return;}
    isLooping_ = true;
    ///todo : poll
    while(!quit_) {
        activeChannels_.clear();
        poller_->Poll(10000, &activeChannels_);
        for(auto & activeChannel : activeChannels_) {
            activeChannel->handleEvent();
        }
    }
    std::cout<< "EventLoop " << this << " start looping" << std::endl;
    isLooping_ = false;
}

void EventLoop::UpdateChannel(Channel *channel) {
    poller_->UpdateChannel(channel);
}

void EventLoop::quit() {
    quit_ = true;
}
}