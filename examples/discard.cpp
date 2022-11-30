//
// Created by rrrr on 22-11-30.
//
#include <iostream>
#include "EventLoop.h"
#include "TcpServer.h"
void onConnection(const EvtHandle::TcpConnectionPtr& conn) {
    if(conn->Connected()) {
        std::cout<<"new connection: "<< conn->getName()
                 <<" from " << conn->getPeerAddr().toIpPort()<<std::endl;
    }
}
void onMessage(const EvtHandle::TcpConnectionPtr& conn, char* buf, timeval tv) {
    if(conn->Connected()) {
        std::cout<<"new message from connection: "<< conn->getName()
                 <<" : " << buf<<std::endl;
    }
}

int main() {
    std::cout<<"main:pid = "<<getpid()<<std::endl;
    EvtHandle::EventLoop loop;
    EvtHandle::InetAddress addr(2022);
    EvtHandle::TcpServer server(&loop,addr, "Discard server");
    server.setConnectionCb(onConnection);
    server.setMessageCb(onMessage);
    server.start();
    loop.loop();
    return 0;
}