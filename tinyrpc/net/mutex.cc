#include  <pthread.h>
#include <memory>
#include "tinyrpc/net/mutex.h"
#include "tinyrpc/net/reactor.h"
#include "tinyrpc/comm/log.h"
#include "tinyrpc/coroutine/coroutine.h"
#include "tinyrpc/coroutine/coroutine_hook.h"


namespace tinyrpc {

CoroutineMutex::CoroutineMutex() {}

CoroutineMutex::~CoroutineMutex() {
    if (m_locked_) {
        unlock();
    }
}

void CoroutineMutex::lock() {
    
}



} //end namespace