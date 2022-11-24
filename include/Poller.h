//
// Created by rrrr on 22-11-22.
//

#ifndef EVTHANDLE_POLLER_H
#define EVTHANDLE_POLLER_H

#include "noncopyable.h"
#include "EventLoop.h"
#include <vector>
#include <map>
#include <poll.h>

struct pollfd;

namespace EvtHandle {
class Channel;

class Poller : noncopyable {
public:
using ChannelList = std::vector<Channel*>;
explicit Poller(EventLoop* loop) : ownerLoop_(loop) {};
~Poller()= default;;
timeval Poll(int timeOutMs, ChannelList* activeChannels);

void UpdateChannel(Channel* channel);
static Poller* newDefaultPoller(EventLoop* loop);
private:
void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

using ChannelMap = std::map<int, Channel*>;
using PollFdList =  std::vector<pollfd>;

PollFdList pollFds_;//struct pollfds
ChannelMap channels_;//fd, fdChannel
EventLoop* ownerLoop_;
};
}
#endif //EVTHANDLE_POLLER_H
