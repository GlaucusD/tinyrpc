#ifndef TINYRPC_COMM_MYSQL_INSTANCE_H
#define TINYRPC_COMM_MYSQL_INSTANCE_H
#include <memory>
#include <map>
#include "tinyrpc/net/mutex.h"
#include "tinyrpc/net/net_address.h"

#ifdef DECLARE_MYSQL_PLUGIN 
#include <mysql/mysql.h>
#endif

namespace tinyrpc {

struct MySQLOption {

};

} // end namespace 
#endif