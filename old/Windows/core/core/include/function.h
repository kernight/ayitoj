#ifndef FUNCTION_H
#define FUNCTION_H 0

#include "head.h"

/*获取文件大小*/
long get_file_size(const char * filename);

/*初始评测机数据*/
int init_param(int argc,char const *argv[],OJ_Info &info);

/*搜索指定目录下所有输入文件,并且把路径存入 que_path*/
void findInfiles(string dir,queue<string>& que_path);

//执行命令行，并转存结果
int my_exec(string cmd, string path, int time_lim);

//比较两个文件是否相同
bool file_cmp(string file1, string file2);

#endif	//FUNCTION_H