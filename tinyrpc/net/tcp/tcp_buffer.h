#ifndef IFNDEF_NET_TCP_BUFFER_H
#define IFNDEF_NET_TCP_BUFFER_H
#include <vector>
#include <memory>
namespace tinyrpc {

class TcpBuffer
{
public:
    using ptr = std::shared_ptr<TcpBuffer>;
    explicit TcpBuffer(int sz);
    ~TcpBuffer();
    int readable();
    int writeable();
    int readIndex() const;
    int writeIndex() const;

    void writeToBuffer(const char* buf, int size);
    void readFromBuffer(std::vector<char>& coll, int size);
    void resizeBuffer(int size);
    void clearBuffer();
    int getSize();
    std::vector<char> getBufferVector();
    std::string getBufferString();
    void recycledRead(int index);
    void recycledWrite(int index);
    void adjustBuffer();
    
    //TODO should this variable be defined as private?
    std::vector<char> m_buffer;
private:
    int m_read_index_{0};
    int m_write_index_{0};
    int m_size_{0};
};


}
#endif