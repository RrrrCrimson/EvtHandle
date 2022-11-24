//
// Created by rrrr on 22-11-24.
//
#include "sys/timerfd.h"
#include "EventLoop.h"
#include "Channel.h"
#include <unistd.h>
#include <iostream>

EvtHandle::EventLoop *g_Loop;

void timeOut() {
    std::cout << "time out" << std::endl;
    g_Loop->quit();
}

int main() {
    EvtHandle::EventLoop loop;
    g_Loop = &loop;
    int timerFd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);

    EvtHandle::Channel channel(&loop, timerFd);
    channel.setReadCallback(timeOut);
    channel.enableReading();

    struct itimerspec howLong{};
    howLong.it_value.tv_sec = 5;
    timerfd_settime(timerFd, 0, &howLong, nullptr);

    loop.loop();
    close(timerFd);
    return 0;
}