//
// Created by rrrr on 22-11-28.
//

#ifndef EVTHANDLE_TCPSERVER_H
#define EVTHANDLE_TCPSERVER_H

#include "noncopyable.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <map>
#include <string>
namespace EvtHandle {
class Acceptor;
class EventLoop;
class TcpServer : noncopyable{
public:
    TcpServer(EventLoop *loop, const InetAddress& listenAddr, std::string name);
    ~TcpServer() = default;
    void start();

    void setConnectionCb(const ConnectionCB &connectionCb);

    void setMessageCb(const MessageCB &messageCb);

private:
    void newConnection(int sockFd, const InetAddress& addr);
    using ConnectionMap = std::map<std::string, TcpConnectionPtr>;
    EventLoop *loop_;
    std::string name_;
    ConnectionCB connectionCb_;
    MessageCB messageCb_;
    std::unique_ptr<Acceptor> acceptor_;
    int nextConnId_{};
    ConnectionMap connections_;
    bool started_{};

};
}
#endif //EVTHANDLE_TCPSERVER_H
