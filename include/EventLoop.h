//
// Created by rrrr on 22-11-22.
//

#ifndef EVTHANDLE_EVENTLOOP_H
#define EVTHANDLE_EVENTLOOP_H
#include "noncopyable.h"
#include <pthread.h>
#include <vector>
#include <memory>

namespace EvtHandle {
class Channel;
class Poller;
class EventLoop : noncopyable {
public :
    EventLoop();
    ~EventLoop();
    void loop();
    void quit();
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
    using ChannelList = std::vector<Channel*>;
    bool isLooping_{};
    bool quit_{};
    const pid_t threadId_{};
    std::unique_ptr<Poller> poller_{};
    ChannelList activeChannels_{};
};
}
#endif //EVTHANDLE_EVENTLOOP_H
