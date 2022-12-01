//
// Created by rrrr on 22-12-1.
//
#include "buffer.h"
#include "socketOps.h"
ssize_t EvtHandle::Buffer::readFd(int fd, int *savedErrno) {
    char extrabuf[65536];
    struct iovec vec[2];
    const size_t writable = writableBytes();
    vec[0].iov_base = begin()+writerIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;
    const int iovLen = (writable < sizeof(extrabuf)?2:1);
    auto n = sockets::readv(fd, vec, iovLen);
    if(n < 0) {
        *savedErrno = errno;
    } else if(n <= writable) {
        writerIndex_+=n;
    } else {
        writerIndex_ = buffer_.size();

    }
    return 0;
}
