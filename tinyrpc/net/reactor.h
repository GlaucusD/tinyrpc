#ifndef TINYRPC_NET_EVENT_LOOP_H
#define TINYRPC_NET_EVENT_LOOP_H

#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <atomic>
#include <map>
#include <functional>
#include <queue>
#include "tinyrpc/coroutine/coroutine.h"
#include "fd_event.h"
#include "mutex.h"

namespace tinyrpc
{
    
enum class ReactorType {
    MainReactor = 1,
    SubReactor
};

class FdEvent;
class Timer;

class Reactor
{
public:
    using ptr = std::shared_ptr<Reactor>;
    explicit Reactor();
    ~Reactor();
    void addEvent(int fd, )
private:

};










} // namespace tinyrpc
#endif