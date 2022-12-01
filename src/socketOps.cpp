//
// Created by rrrr on 22-11-27.
//
#include "socketOps.h"

namespace EvtHandle::sockets {
int createNonblocking(sa_family_t family) {
    int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        std::cout << "sockets::createNonblocking" << std::endl;
    }
    return sockfd;
}

int connect(int sockfd, const struct sockaddr *addr) {
    return ::connect(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in)));
}

void bind(int sockfd, const struct sockaddr *addr) {
    int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in)));
    if (ret < 0) {
        std::cout << "sockets::bindOrDie" << std::endl;
    }
}

void listen(int sockfd) {
    int ret = ::listen(sockfd, SOMAXCONN);
    if (ret < 0) {
        std::cout << "sockets::listenOrDie" << std::endl;
    }
}

int accept(int sockfd, struct sockaddr_in *addr) {
    auto addrlen = static_cast<socklen_t>(sizeof *addr);
#if defined (NO_ACCEPT4)
    int connfd = ::accept(sockfd, sockaddr_cast(addr), &addrlen);
setNonBlockAndCloseOnExec(connfd);
#else
    int connfd = ::accept4(sockfd, (sockaddr *) addr,
                           &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
#endif
    if (connfd < 0) {
        int savedErrno = errno;
        std::cout << "Socket::accept" << std::endl;
        switch (savedErrno) {
            case EMFILE: // per-process lmit of open file desctiptor ???
                // expected errors
                errno = savedErrno;
                break;
            case EOPNOTSUPP:
                // unexpected errors
                std::cout << "unexpected error of ::accept " << savedErrno << std::endl;
                break;
            default:
                std::cout << "unknown error of ::accept " << savedErrno << std::endl;
                break;
        }
    }
    return connfd;
}

ssize_t read(int sockfd, void *buf, size_t count) {
    return ::read(sockfd, buf, count);
}

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt) {
    return ::readv(sockfd, iov, iovcnt);
}

ssize_t write(int sockfd, const void *buf, size_t count) {
    return ::write(sockfd, buf, count);
}

void close(int sockfd) {
    if (::close(sockfd) < 0) {
        std::cout << "sockets::close" << std::endl;
    }
}

void shutdownWrite(int sockfd) {
    if (::shutdown(sockfd, SHUT_WR) < 0) {
        std::cout << "sockets::shutdownWrite" << std::endl;
    }
}

void toIp(char *buf, size_t size,
          const struct sockaddr *addr) {
    const struct sockaddr_in *addr4 = (sockaddr_in *) addr;
    ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
}

void toIpPort(char *buf, size_t size,
              const struct sockaddr *addr) {
    toIp(buf, size, addr);
    size_t end = ::strlen(buf);
    const struct sockaddr_in *addr4 = (sockaddr_in *) (addr);
    uint16_t port = be16toh(addr4->sin_port);
    snprintf(buf + end, size - end, ":%u", port);
}

struct sockaddr_in getLocalAddr(int sockfd)
{
    struct sockaddr_in localaddr{};
    auto addrlen = static_cast<socklen_t>(sizeof localaddr);
    if (::getsockname(sockfd, (sockaddr*)(&localaddr), &addrlen) < 0)
    {
        std::cout << "sockets::getLocalAddr" << std::endl;
    }
    return localaddr;
}

struct sockaddr_in getPeerAddr(int sockfd)
{
    struct sockaddr_in peeraddr{};
    auto addrlen = static_cast<socklen_t>(sizeof peeraddr);
    if (::getpeername(sockfd, (sockaddr*)(&peeraddr), &addrlen) < 0)
    {
        std::cout << "sockets::getPeerAddr" << std::endl;
    }
    return peeraddr;
}

}