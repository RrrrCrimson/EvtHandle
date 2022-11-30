//
// Created by rrrr on 22-11-28.
//
#include "TcpServer.h"
#include "Channel.h"
namespace EvtHandle {

    void TcpServer::setConnectionCb(const ConnectionCB &connectionCb) {
        connectionCb_ = connectionCb;
    }

    void TcpServer::setMessageCb(const MessageCB &messageCb) {
        messageCb_ = messageCb;
    }

    void TcpServer::newConnection(int sockFd, const InetAddress &addr) {
        char buf[32];
        snprintf(buf,sizeof(buf), "#%d",nextConnId_++);
        std::string connName = name_+ buf;
        std::cout << "TcpServer::newConnection [" << name_
                 << "] - new connection [" << connName
                 << "] from " << addr.toIpPort() << std::endl;
        InetAddress localAddr(sockets::getLocalAddr(sockFd));
        TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockFd, localAddr, addr));
        connections_[connName] = conn;
        conn->setConnectionCallback(connectionCb_);
        conn->setMessageCallback(messageCb_);
        conn->connectEstablished();
    }

    TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr, std::string name) :
                         loop_(loop),
                         acceptor_(new Acceptor(loop_, listenAddr)),
                         name_(std::move(name)),
                         nextConnId_(1),
                         started_(false) {
        acceptor_->setCb([this](auto && PH1, auto && PH2)
            { newConnection(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); }
        );
    }

    void TcpServer::start() {
        if(!started_) {
            started_ = true;
            acceptor_->Listen();
        }
    }
}