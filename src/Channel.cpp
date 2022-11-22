//
// Created by rrrr on 22-11-22.
//
#include "Channel.h"
#include <poll.h>
#include "EventLoop.h"
namespace EvtHandle {
const int Channel::kNoneEvent_ = 0;
const int Channel::kReadEvent_ = POLLIN | POLLPRI;
const int Channel::kWriteEvent_ = POLLOUT;
Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop),
      fd_(fd),
      events_(0),
      revents_(0),
      index_(-1) {}

void Channel::update() {
    loop_->UpdateChannel(this);
}

void Channel::handleEvent() {
    if (revents_ & (POLLERR | POLLNVAL)) {
        if (errorCB_) errorCB_();
    }
    if (revents_ & (POLLRDHUP | POLLIN | POLLPRI)) {
        if (readCB_) readCB_();
    }
    if (revents_ & POLLOUT) {
        if (writeCB_) writeCB_();
    }
}
}