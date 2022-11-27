//
// Created by rrrr on 22-11-26.
//

#ifndef EVTHANDLE_SOCKETOPS_H
#define EVTHANDLE_SOCKETOPS_H

#include <arpa/inet.h>
#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/uio.h>  // readv
#include <unistd.h>

namespace EvtHandle::sockets {
int createNonblocking(sa_family_t family);

int connect(int sockfd, const struct sockaddr *addr);

void bind(int sockfd, const struct sockaddr *addr);

void listen(int sockfd);

int accept(int sockfd, struct sockaddr_in *addr);

ssize_t read(int sockfd, void *buf, size_t count);

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);

ssize_t write(int sockfd, const void *buf, size_t count);

void close(int sockfd);

void shutdownWrite(int sockfd);

void toIp(char *buf, size_t size, const struct sockaddr *addr);

void toIpPort(char *buf, size_t size, const struct sockaddr *addr);
}
#endif //EVTHANDLE_SOCKETOPS_H
