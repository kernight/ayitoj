#ifndef FUNCTION_H
#define FUNCTION_H 0

#include "head.h"

/*获取进程指定状态*/
int get_proc_status(int pid, const char * mark);

/*获取用户内容*/
long get_file_size(const char * filename);

/*初始评测机数据*/
int init_param(int argc,char const *argv[],OJ_Info &info);

/*搜索指定目录下所有输入文件,并且把路径存入 que_path*/
void findInfiles(string dir,queue<string>& que_path);

#endif	//FUNCTION_H