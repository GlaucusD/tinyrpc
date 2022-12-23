#include <unistd.h>
#include <cstring>
#include "tinyrpc/net/tcp/tcp_buffer.h"
#include "tinyrpc/comm/log.h"
#include <string>
namespace tinyrpc {

TcpBuffer::TcpBuffer(int sz) { m_buffer.resize(sz);}
TcpBuffer::~TcpBuffer() = default;
int TcpBuffer::readable() {m_write_index_ - m_read_index_;}
int TcpBuffer::writeable() {return m_buffer.size() - m_write_index_;}
int TcpBuffer::readIndex() const { return m_read_index_;}
int TcpBuffer::writeIndex() const { return m_write_index_;}
void TcpBuffer::resizeBuffer(int size) {
    std::vector<char> tmp(size);
    int c = std::min(size, readable());
    memcpy(&tmp[0], &m_buffer[m_read_index_], c);
    m_buffer.swap(tmp);
    m_read_index_ = 0;
    m_write_index_ = c;
}

void TcpBuffer::writeToBuffer(const char* buf, int size) {
    if (size > writeable()) {
        int new_size = (int)(1.5 * (m_write_index_ + size));
        resizeBuffer(new_size);
    }
    memcpy(&m_buffer[m_write_index_], buf, size);
    m_write_index_ += size;
    
}

void TcpBuffer::readFromBuffer(std::vector<char>& coll, int size) {
    if (!readable()) {
        //TODO DebugLog << "buffer is empty\n";
        return;
    }
    int read_size = readable() > size ? size : readable();
    std::vector<char> tmp(read_size);
    bzero(&tmp[0],0);
    memcpy(&tmp[0], &m_buffer[m_read_index_], read_size);
    coll.swap(tmp);
    m_read_index_ += read_size;
    adjustBuffer();
}

void TcpBuffer::adjustBuffer() {
    if (m_read_index_ > static_cast<int>(m_buffer.size() / 3)) {
        std::vector<char> new_buf(m_buffer.size());
        bzero(&new_buf[0], 0);
        int cnt = readable();
        memcpy(&new_buf[0], &m_buffer[m_read_index_], cnt);
        m_buffer.swap(new_buf);
        m_read_index_ = 0;
        m_write_index_ = cnt;
        new_buf.clear();
    }
}

int TcpBuffer::getSize() { return m_buffer.size(); }

void TcpBuffer::clearBuffer() {
    m_buffer.clear();
    m_read_index_ = m_write_index_ = 0;
}

void TcpBuffer::recycledRead(int index) {
    int j = m_read_index_ = index;
    if (j > (int)m_buffer.size()) {
        //TODO
        return;
    }
    m_read_index_ = j;
    adjustBuffer();
}

void TcpBuffer::recycledWrite(int index) {
    int j = m_write_index_ = index;
    if (j > (int)m_buffer.size()) {
        //TODO
        return;
    }
    m_write_index_ = j;
    adjustBuffer();
}

std::string TcpBuffer::getBufferString() {
    int sz = readable();
    std::string re(sz,'0');
    memcpy(&re[0], &m_buffer[m_read_index_], sz);
    return re;
}

std::vector<char> TcpBuffer::getBufferVector() {return m_buffer;}

} //namespace tinyrpc