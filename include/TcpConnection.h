//
// Created by rrrr on 22-11-28.
//

#ifndef EVTHANDLE_TCPCONNECTION_H
#define EVTHANDLE_TCPCONNECTION_H
#include "noncopyable.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include <string>
#include <memory>
#include <functional>
namespace EvtHandle {
class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TimerCB = std::function<void()>;
using ConnectionCB = std::function<void (const TcpConnectionPtr&)>;
using MessageCB = std::function<void (const TcpConnectionPtr&, char*, timeval)>;

class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop *loop, std::string name, int fd, const InetAddress& localAddr, const InetAddress& peerAddr);

    void connectEstablished();
    void setConnectionCallback(const ConnectionCB& cb)
    { connectionCb_ = cb; }

    void setMessageCallback(const MessageCB& cb)
    { messageCb_ = cb; }
    bool Connected() {return state_ == connected;}

    const std::string &getName() const;

    const InetAddress &getPeerAddr() const;

    EventLoop *getLoop() const;

    const InetAddress &getLocalAddr() const;
private:
    enum State {
        connected,
        connecting
    };
    void setState(State state);
    void handleRead();
    EventLoop *loop_;
    std::string name_;
    State state_;
    ConnectionCB connectionCb_;
    MessageCB messageCb_;
    InetAddress localAddr_;
    InetAddress peerAddr_;
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
};
}
#endif //EVTHANDLE_TCPCONNECTION_H
