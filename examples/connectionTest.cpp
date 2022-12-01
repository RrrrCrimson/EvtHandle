//
// Created by rrrr on 22-11-27.
//
#include "InetAddress.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include <iostream>
#include <unistd.h>
void onConnection(int fd, const EvtHandle::InetAddress& addr) {
    std::cout<<"new connection from:"<<addr.toIpPort()<<std::endl;
    write(fd,"hello,world\n",12);
}

int main() {
    std::cout<<"main:pid = "<<getpid()<<std::endl;
    EvtHandle::EventLoop loop;
    EvtHandle::InetAddress addr(2022);
    EvtHandle::Acceptor acceptor(&loop, addr);
    acceptor.setCb(onConnection);
    acceptor.Listen();

    loop.loop();
    return 0;
}