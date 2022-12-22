#include <tinyxml/tinyxml.h>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <memory>
#include "tinyrpc/comm/config.h"
#include "tinyrpc/comm/log.h"
#include "tinyrpc/net/net_address.h"
#include "tinyrpc/net/tcp/tcp_server.h"


namespace tinyrpc {
    extern tinyrpc::Logger::ptr gRpcLogger;
    extern tinyrpc::TcpServer::ptr gRpcServer;

    Config::Config(const char * file_path) :m_log_path(std::string(file_path)) {
        m_xml_file = new TiXmlDocument();
        bool rt;
        if(!(rt = m_xml_file->LoadFile(file_path))) {
             printf("start tinyrpc server error! read conf file [%s] error info: [%s], errorid: [%d], error_row_column:[%d row %d column]\n", 
            file_path, m_xml_file->ErrorDesc(), m_xml_file->ErrorId(), m_xml_file->ErrorRow(), m_xml_file->ErrorCol());
            exit(0);
        }
    }

    

}
