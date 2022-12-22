#ifndef TINYRPC_COMM_CONFIG_H
#define TINYRPC_COMM_CONFIG_H
//#include <tinyxml/tinyxml.h>
#include <memory>
#include <map>
#include <string>

#ifdef DECLARE_MYSQL_PLUGIN
#include "tinyrpc/comm/mysql_instase.h"
#endif

namespace tinyrpc {

enum class LogLevel {
    DEBUG = 1,
    INFO,
    WARN,
    ERROR,
    NONE
};

class Config {
public:
    using ptr = std::shared_ptr<Config>;
    Config(const char* file_path);
    ~Config();
    void readConfig();
    void readDBConfig(TiXmlElement* node);
    void readLogConfig(TiXmlElement* node);
    TiXmlElement* getXmlNode(const std::string& name);

public:
    //  log parameters.
    std::string m_log_path;
    std::string m_log_prefix;
    int m_log_max_size{0};
    LogLevel m_log_level{LogLevel::DEBUG};
    int m_log_sync_inteval{500};

    // coroutine parameters
    int m_cor_stack_size{0};
    int m_cor_pool_size{0};
    int m_msg_req_len{0};

    int m_max_connect_timeout{0}; //ms
    int m_iothread_num{0};
    int m_timewheel_bucket_num {0};
    int m_timewhell_inteval{0};
    #ifdef DECLARE_MYSQL_PLUGIN
    std::map<std::string, MySQLOption> m_mysql_options;
    #endif

private:
    std::string m_file_path;
    TiXmlDocument* m_xml_file;
};


}

#endif