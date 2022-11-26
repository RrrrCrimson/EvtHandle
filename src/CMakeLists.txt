set(SRCS
    EventLoop.cpp
    Channel.cpp
    Poller.cpp
    Socket.cpp
    InetAddress.cpp
    Acceptor.cpp
        )

add_library(EvtHandleNet ${SRCS})