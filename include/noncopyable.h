//
// Created by rrrr on 22-11-22.
//

#ifndef EVTHANDLE_NONCOPYABLE_H
#define EVTHANDLE_NONCOPYABLE_H
namespace EvtHandle {
class noncopyable {
public:
    noncopyable(const noncopyable &) = delete;

    void operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;

    ~noncopyable() = default;
};

}
#endif //EVTHANDLE_NONCOPYABLE_H
