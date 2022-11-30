set(SRCS
    EventLoop.cpp
    Channel.cpp
    Poller.cpp
    Socket.cpp
    InetAddress.cpp
    Acceptor.cpp
    socketOps.cpp TcpServer.cpp TcpConnection.cpp)

add_library(EvtHandleNet ${SRCS})