#ifndef TINYRPC_NET_CODEC_H
#define TINYRPC_NET_CODEC_H
#include <memory>
#include <string>
#include "tcp/tcp_buffer.h"
#include "abstract_data.h"
namespace tinyrpc{
enum class ProtocolType {
    TinyPb_Protocol = 1,
    Http_Protocol
};
class AbstractCodec 
{
public:
    using ptr = std::shared_ptr<AbstractCodec>;
    AbstractCodec();
    virtual ~AbstractCodec(){};
    virtual void encode(TcpBuffer* buf, AbstractData* data) = 0; //pure virtual function.
    virtual void decode(TcpBuffer* buf, AbstractData* data) = 0;
    virtual ProtocolType getProtocolType() = 0;
};
} //namespace tinyrpc
#endif