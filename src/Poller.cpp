//
// Created by rrrr on 22-11-22.
//
#include "Poller.h"
#include "Channel.h"
#include <poll.h>
#include <sys/time.h>
#include <iostream>
namespace EvtHandle {

timeval Poller::Poll(int timeOutMs, Poller::ChannelList *activeChannels) {
    int numEvents = poll(&*pollFds_.begin(), pollFds_.size(), timeOutMs);
    timeval tv{};
    gettimeofday(&tv, nullptr);
    if (numEvents > 0)
    {
        std::cout << numEvents << " events happened"<<std::endl;
        fillActiveChannels(numEvents, activeChannels);
    }
    else if (numEvents == 0)
    {
        std::cout << "nothing happened"<<std::endl;
    }
    else
    {
        // error happens, log uncommon ones
        if (errno != EINTR)
        {
            std::cout << "EPollPoller::poll()"<<std::endl;
        }
    }
    return tv;
}

void Poller::UpdateChannel(Channel *channel) {
    const int index = channel->index();
    std::cout << "fd = " << channel->fd()
              << " events = " << channel->events() << " index = " << index << std::endl;
    if(index < 0) {
        //new one to be added
        if(channels_.find(channel->fd()) != channels_.end()) {
            std::cout << "error occurs while Poller::UpdateChannel();" << std::endl;
            return;
        }
        struct pollfd tmp{};
        tmp.fd = channel->fd();
        tmp.events = static_cast<short>(channel->events());
        tmp.revents = 0;
        pollFds_.push_back(tmp);
        auto idx = pollFds_.size()-1;
        channel->set_index(idx);
        channels_[tmp.fd] = channel;
    } else {
        //update existed one
        if(channels_.find(channel->fd()) == channels_.end() || channels_[channel->fd()] != channel) {
            std::cout << "error occurs while Poller::UpdateChannel();" << std::endl;
            return;
        }
        auto &pfd = pollFds_[channel->index()];
        if(pfd.fd != channel->fd() || pfd.fd == -1) {
            std::cout << "fd not available while Poller::UpdateChannel();" << std::endl;
            return;
        }
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        if(channel->isNoneEvent()) {
            pfd.fd = -1;
        }
    }
}

void Poller::fillActiveChannels(int numEvents, Poller::ChannelList *activeChannels) const {
    for(auto pfd = pollFds_.begin();pfd!=pollFds_.end() && numEvents > 0;++pfd) {
        if(pfd->revents > 0) {
            --numEvents;
            auto ch = channels_.find(pfd->fd);
            if(ch != channels_.end()) {
                auto *chan = ch->second;
                chan->set_revents(pfd->revents);
                activeChannels->push_back(chan);
            }
        }
    }
}
}