#ifndef FUNCTION_H
#define FUNCTION_H 0

#include "head.h"

/*��ȡ�ļ���С*/
long get_file_size(const char * filename);

/*��ʼ���������*/
int init_param(int argc,char const *argv[],OJ_Info &info);

/*����ָ��Ŀ¼�����������ļ�,���Ұ�·������ que_path*/
void findInfiles(string dir,queue<string>& que_path);

//ִ�������У���ת����
int my_exec(string cmd, string path, int time_lim);

//�Ƚ������ļ��Ƿ���ͬ
bool file_cmp(string file1, string file2);

#endif	//FUNCTION_H