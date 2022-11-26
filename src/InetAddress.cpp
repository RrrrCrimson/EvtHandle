//
// Created by rrrr on 22-11-24.
//
#include "InetAddress.h"
#include "socketOps.h"
#include <endian.h>

namespace EvtHandle {
static const in_addr_t kInaddrAny = INADDR_ANY;
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;

InetAddress::InetAddress(uint16_t port, bool loopbackOnly) {
    addr_ = sockaddr_in{};
    addr_.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? kInaddrLoopback : kInaddrAny;
    addr_.sin_addr.s_addr = htobe32(ip);
    addr_.sin_port = htobe16(port);
}

InetAddress::InetAddress(const char *ip, uint16_t port) {
    addr_ = sockaddr_in{};
    addr_.sin_family = AF_INET;
    addr_.sin_port = htobe16(port);
    if (::inet_pton(AF_INET, ip, &addr_.sin_addr) <= 0)
    {
        std::cout << "sockets::fromIpPort" << std::endl;
    }
}
}