//
// Created by rrrr on 22-11-24.
//

#ifndef EVTHANDLE_INETADDRESS_H
#define EVTHANDLE_INETADDRESS_H

#include <netinet/in.h>
#include <string>

namespace EvtHandle {
class InetAddress {
public:
    explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);

    InetAddress(const char *ip, uint16_t port);

    explicit InetAddress(const struct sockaddr_in &addr)
            : addr_(addr) {}

    [[nodiscard]] sa_family_t family() const { return addr_.sin_family; }

    [[nodiscard]] const struct sockaddr *getSockAddr() const { return (sockaddr *) (&addr_); }

    void setSockAddrInet(const struct sockaddr_in &addr) { addr_ = addr; }

    [[nodiscard]] std::string toIpPort() const;

    [[nodiscard]] std::string toIp() const;

    static bool resolve(const char *hostname, InetAddress *result);

private:
    struct sockaddr_in addr_{};

};
}

#endif //EVTHANDLE_INETADDRESS_H
