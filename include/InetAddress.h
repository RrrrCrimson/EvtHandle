//
// Created by rrrr on 22-11-24.
//

#ifndef EVTHANDLE_INETADDRESS_H
#define EVTHANDLE_INETADDRESS_H
#include <netinet/in.h>

namespace EvtHandle {
class InetAddress {
public:
    explicit InetAddress(const struct sockaddr_in& addr)
            : addr_(addr)
    { }

    [[nodiscard]] sa_family_t family() const { return addr_.sin_family; }
    [[nodiscard]] const struct sockaddr* getSockAddr() const { return (sockaddr*)(&addr_); }
    void setSockAddrInet(const struct sockaddr_in& addr) { addr_ = addr; }

    static bool resolve(const char* hostname, InetAddress* result);

private:
    struct sockaddr_in addr_;

};
}

#endif //EVTHANDLE_INETADDRESS_H
