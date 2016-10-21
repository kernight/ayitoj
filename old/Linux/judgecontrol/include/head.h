#ifndef HEAD_H
#define HEAD_H 0
#define MYSQLPP_MYSQL_HEADERS_BURIED  

using namespace std;

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <cstdlib>


#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#include <syslog.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <assert.h>

#include <mysql++/mysql++.h>

/*自定义文件*/
#include "error.h"
#include "const.h"
#include "log.h"
#include "config.h"
#include "database.h"
#include "function.h"

#endif	//HEAD_H