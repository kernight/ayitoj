#ifndef FUNCTION_H
#define FUNCTION_H 0

#include "head.h"

/*获取进程指定状态*/
int get_proc_status(int pid, const char * mark);

/*获取文件大小*/
long get_file_size(const char * filename);

/*初始守护进程*/
int init_damon();

#endif	//FUNCTION_H