//
// Created by rrrr on 22-11-26.
//

#ifndef EVTHANDLE_ACCEPTOR_H
#define EVTHANDLE_ACCEPTOR_H
#include "noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"
#include <functional>
namespace EvtHandle{
class EventLoop;
class InetAddress;

class Acceptor : noncopyable {
public:
    using ConnectionCB = std::function<void(int fd, const InetAddress&)> ;
    Acceptor(EventLoop*, const InetAddress&);

    void setCb(const ConnectionCB &cb);
    [[nodiscard]] bool isListening() const {return isListening_;};
    void Listen();

private:
    void handleRead();
    EventLoop* loop_;
    Socket acceptSocket_;//an RAII Server socket
    Channel acceptChannel_;
    ConnectionCB cb_;
    bool isListening_;
};
}
#endif //EVTHANDLE_ACCEPTOR_H
