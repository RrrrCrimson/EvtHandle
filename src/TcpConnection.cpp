//
// Created by rrrr on 22-11-28.
//
#include "TcpConnection.h"

#include "Channel.h"
#include <utility>
#include <functional>
namespace EvtHandle {

void TcpConnection::setState(TcpConnection::State state) {
    state_ = state;
}

void TcpConnection::handleRead() {
    char buf[65535];
    auto n = read(channel_->fd(), buf, sizeof(buf));
    timeval tv{};
    messageCb_(shared_from_this(), buf, tv);
}

TcpConnection::TcpConnection(EventLoop *loop,
                             std::string name,
                             int fd,
                             const InetAddress &localAddr,
                             const InetAddress &peerAddr) :
                             loop_(loop),
                             name_(std::move(name)),
                             socket_(new Socket(fd)),
                             channel_(new Channel(loop_, socket_->fd())),
                             state_(connecting),
                             localAddr_(localAddr),
                             peerAddr_(peerAddr)
{
    channel_->setReadCallback([this] { handleRead(); });
}

void TcpConnection::connectEstablished() {
    setState(connected);
    channel_->enableReading();
    connectionCb_(shared_from_this());
}

const std::string &TcpConnection::getName() const {
    return name_;
}

const InetAddress &TcpConnection::getPeerAddr() const {
    return peerAddr_;
}

EventLoop *TcpConnection::getLoop() const {
    return loop_;
}

const InetAddress &TcpConnection::getLocalAddr() const {
    return localAddr_;
}
}