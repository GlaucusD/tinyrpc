#ifndef TINYRPC_NET_MUTEX_H
#define TINYRPC_NET_MUTEX_H

#include <pthread.h>
#include <memory>
#include <queue>
#include "tinyrpc/coroutine/coroutine.h"

namespace tinyrpc 
{

template<class T>
struct ScopedLockImpl
{
public:
    ScopedLockImpl(T& mutex) : m_mutex_(mutex)  {
        m_mutex_.lock();
        m_locked_ = true;
    }
    ~ScopedLockImpl() { unlock();}

    void lock() {
        if (!m_locked_) {
            m_mutex_.lock();
            m_locked_ = true;
        }
    }

    void unlock() {
        if (m_locked_) {
            m_mutex_.unlock();
            m_locked_ = false;
        }
    }

private:
    T& m_mutex_;
    bool m_locked_;
};

template<class T>
struct ReadSocopedLockImpl 
{
public:
    ReadSocopedLockImpl(T& mutex) :m_mutex_(mutex) {
        m_mutex_.rdlock();
        m_locked_ = true;
    }
    ~ReadSocopedLockImpl() {unlock();}

    void lock() {
        if (!m_locked_) {
            m_mutex_.rdlock();
            m_locked_ = true;
        }
    }

    void unlock() {
        if (m_locked_) {
            m_mutex_.unlock();
            m_locked_ = false;
        }
    }
private:
    T& m_mutex_;
    bool m_locked_;
};

template<class T>
struct WriteScopedLockImpl 
{
public:
    WriteScopedLockImpl(T& mutex) :m_mutex_(mutex) {
        m_mutex_.wrlock();
        m_locked_ = true;
    }
    ~WriteScopedLockImpl () {unlock();}

    void lock() {
        if (!m_locked_) {
            m_mutex_.wrlock();
            m_locked_ = true;
        }
    }

    void unlock() {
        if (m_locked_) {
            m_mutex_.unlock();
            m_locked_ = false;
        }
    }
private:
    T& m_mutex_;
    bool m_locked_;
};

class Mutex 
{
public:
    using Lock = ScopedLockImpl<Mutex>;
    Mutex() { pthread_mutex_init(&m_mutex_,NULL);}
    ~Mutex() {pthread_mutex_destory(&m_mutex_);}
    void lock() { pthread_mutex_lock(&m_mutex_);}
    void unlock() {pthread_mutex_unlock(&m_mutex_);}
private:
    pthread_mutex_t m_mutex_;
};


class RWMutex 
{
public:
    using ReadLock = ReadSocopedLockImpl<RWMutex>;
    using WriteLock = WriteScopedLockImpl<RWMutex>;
    RWMutex() {pthread_mutex_init(&m_mutex_, NULL);}
    ~RWMutex() {pthread_mutex_destory(&m_mutex_);}
    void rdlock() {pthread_rwlock_rdlock(&m_lock); }
    void wrlock() {pthread_rwlock_wrlock(&m_lock);}
    void unlock(){pthread_rwlock_unlock(&m_lock);}
private:
    pthread_mutex_t m_mutex_;
};

class CoroutineMutex
{
public:
    using Lock = ScopedLockImpl<CoroutineMutex>;
    CoroutineMutex();
    ~CoroutineMutex();
    void lock();
    void unlock();
private:
    bool m_locked_{false};
    Mutex m_mutex_;
    std::queue<CoroutineMutex*> m_sleep_cors_;
};
void CououtineLock();
void CououtineUnLock();

}// end namespace

#endif 