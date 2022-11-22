//
// Created by rrrr on 22-11-22.
//

#ifndef EVTHANDLE_EVENTLOOP_H
#define EVTHANDLE_EVENTLOOP_H
#include "noncopyable.h"
#include <pthread.h>

namespace EvtHandle {
class Channel;
class Poller;
class EventLoop : noncopyable {
public :
    EventLoop();
    ~EventLoop();
    void loop();
    void UpdateChannel(Channel* channel);
//    bool IsInLoopThread() const {
//        return threadId_ == pthread_self();
//    }
//    void assertInLoopThread() {
//        if(!IsInLoopThread()) {
//            abortNotInLoopThread();
//        }
//    }
private:
    void abortNotInLoopThread();
    bool isLooping_;
    const pid_t threadId_;
};
}
#endif //EVTHANDLE_EVENTLOOP_H
