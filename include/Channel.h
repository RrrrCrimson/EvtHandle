//
// Created by rrrr on 22-11-22.
//

#ifndef EVTHANDLE_CHANNEL_H
#define EVTHANDLE_CHANNEL_H

#include "noncopyable.h"
#include <functional>

namespace EvtHandle {
class EventLoop;

class Channel : noncopyable {
public:
    using EeventCB = std::function<void()>;

    Channel(EventLoop *loop, int fd);

    void handleEvent();

    void setReadCallback(EeventCB cb) { readCB_ = std::move(cb); }

    void setWriteCallback(EeventCB cb) { writeCB_ = std::move(cb); }

    void setErrorCallback(EeventCB cb) { errorCB_ = std::move(cb); }

    void enableReading() {
        events_ |= kReadEvent_;
        update();
    }

    void disableReading() {
        events_ &= ~kReadEvent_;
        update();
    }

    void enableWriting() {
        events_ |= kWriteEvent_;
        update();
    }

    void disableWriting() {
        events_ &= ~kWriteEvent_;
        update();
    }

    void disableAll() {
        events_ = kNoneEvent_;
        update();
    }

    [[nodiscard]] bool isWriting() const { return events_ & kWriteEvent_; }

    [[nodiscard]] bool isReading() const { return events_ & kReadEvent_; }

    [[nodiscard]] int fd() const { return fd_; }

    [[nodiscard]] int events() const { return events_; }

    void setRevents(int revt) { revents_ = revt; } // used by pollers
    [[nodiscard]] bool isNoneEvent() const { return events_ == kNoneEvent_; }

    // for Poller
    [[nodiscard]] int index() const { return index_; }

    void setIndex(int idx) { index_ = idx; }

    EventLoop *ownerLoop() { return loop_; }

private:
    void update();

    static const int kNoneEvent_;
    static const int kReadEvent_;
    static const int kWriteEvent_;
    EventLoop *loop_;
    const int fd_;
    int events_;
    int revents_;
    int index_;

    EeventCB readCB_;
    EeventCB writeCB_;
    EeventCB errorCB_;
};
}

#endif //EVTHANDLE_CHANNEL_H
