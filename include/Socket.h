//
// Created by rrrr on 22-11-24.
//

#ifndef EVTHANDLE_SOCKET_H
#define EVTHANDLE_SOCKET_H
#include "socketOps.h"
namespace EvtHandle {
class InetAddress;
class Socket {
public:
    explicit Socket(int sockFd) : sockFd_(sockFd) {};
    ~Socket();

    [[nodiscard]] inline int fd() const {return sockFd_;};

    void bindAddress(const InetAddress& localAddr) const;
    void listen() const;
    int accept(InetAddress* peeraddr) const;

    void shutdownWrite() const;
    /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
    void setTcpNoDelay(bool on) const;
    /// Enable/disable SO_REUSEADDR
    void setReuseAddr(bool on) const;
    /// Enable/disable SO_REUSEPORT
    void setReusePort(bool on) const;
    /// Enable/disable SO_KEEPALIVE
    void setKeepAlive(bool on);
private:
    const int sockFd_;
};
}

#endif //EVTHANDLE_SOCKET_H
