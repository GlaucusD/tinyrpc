#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <random>
#include "tinyrpc/comm/log.h"
#include "tinyrpc/comm/msg_req.h"
#include "tinyrpc/comm/config.h"

namespace tinyrpc {
extern tinyrpc::Config::ptr gRpcConfig;
static thread_local std::string t_msg_req_nu;
static thread_local std::string t_max_msg_req_nu;
static int g_random_fd = -1; //file descriptor.

std::string MsgReqUtil::getMsgNumber() {
    
}

}// namespace tinyrpc