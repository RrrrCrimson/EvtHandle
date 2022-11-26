//
// Created by rrrr on 22-11-24.
//
#include "Socket.h"
#include "InetAddress.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

namespace EvtHandle {

Socket::~Socket() {
    sockets::close(sockFd_);
}

void Socket::bindAddress(const InetAddress &localAddr) const {
    sockets::bind(sockFd_, localAddr.getSockAddr());
}

void Socket::listen() const {
    sockets::listen(sockFd_);
}

void Socket::shutdownWrite() const {
    sockets::shutdownWrite(sockFd_);
}

int Socket::accept(InetAddress *peeraddr) const {
    struct sockaddr_in addr{};
    int connFd = sockets::accept(sockFd_, &addr);
    if(connFd >= 0) {
        peeraddr->setSockAddrInet(addr);
    }
    return connFd;
}


void Socket::setTcpNoDelay(bool on) const {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, IPPROTO_TCP, TCP_NODELAY,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

void Socket::setReuseAddr(bool on) const {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, SOL_SOCKET, SO_REUSEADDR,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

void Socket::setReusePort(bool on) const {
#ifdef SO_REUSEPORT
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(sockFd_, SOL_SOCKET, SO_REUSEPORT,
                           &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0 && on) {
        std::cout << "SO_REUSEPORT failed." << std::endl;
    }
#else
    if (on)
    {
        LOG_ERROR << "SO_REUSEPORT is not supported.";
    }
#endif
}

void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(sockFd_, SOL_SOCKET, SO_KEEPALIVE,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

}