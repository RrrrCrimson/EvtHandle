//
// Created by rrrr on 22-11-26.
//
#include "Acceptor.h"

namespace EvtHandle{

void Acceptor::setCb(const Acceptor::ConnectionCB &cb) {
    cb_ = cb;
}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &addr)
    : loop_(loop),
      acceptSocket_(sockets::createNonblocking(AF_INET)),
      acceptChannel_(loop_, acceptSocket_.fd()),
      isListening_(false)
{
    acceptSocket_.bindAddress(addr);
    acceptSocket_.setReuseAddr(true);
    acceptChannel_.setReadCallback([this] { handleRead(); });
}
//actually start from here
void Acceptor::Listen() {
    isListening_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading();
}

void Acceptor::handleRead() {
    InetAddress peerAddr{};
    int connFd = acceptSocket_.accept(&peerAddr);
    if(connFd >= 0) {
        if(cb_) {
            cb_(connFd, peerAddr);
        } else {
            close(connFd);
        }
    }
    // FIXME:error handle
}
}