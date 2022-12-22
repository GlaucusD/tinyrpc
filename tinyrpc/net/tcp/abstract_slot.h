#ifndef TINYRPC_NET_TCP_ABSTRACTSLOT_H
#define TINYRPC_NET_TCP_ABSTRACTSLOT_H

#include <functional>
#include <memory>

namespace tinyrpc
{

template <class T>
class AbstractSlot 
{
public:
    using ptr = std::shared_ptr<AbstractSlot>;
    using weakPtr = std::shared_ptr<T>;
    using sharedPtr = std::shared_ptr<T>;
    AbstractSlot(weakPtr ptr, std::function<void(sharedPtr)> cb) :m_weak_ptr_(ptr), m_cb_(cb) {}
    ~AbstractSlot() {
        sharedPtr ptr = m_weak_ptr_.lock();
        if (ptr) {
            m_cb_(ptr);
        }
    }


private:
    weakPtr m_weak_ptr_;
    std::function<void(sharedPtr)> m_cb_;
};



} // namespace tinyrpc

#endif 