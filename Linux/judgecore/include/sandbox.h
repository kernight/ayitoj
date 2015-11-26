#ifndef SANDBOX_H
#define SANDBOX_H 0

/*沙箱运行模块*/

#include "head.h"

#define STD_KB 1024
#define STD_MB (1024*1024)
#define STD_T_LIM 2
#define STD_F_LIM  32768
#define STD_M_LIM 8192
#define BUFFER_SIZE 1024

class Sandbox
{
public:
	Sandbox(OJ_Info info);
	~Sandbox(){};

	/*C/C++程序*/
	OJ_Reinfo cpp();

	/*子进程运行C/C++程序*/
	int run_cpp();

	/*
	*检测C/C++程序运行情况
	*pid_t pid 子进程id
	*/
	OJ_Reinfo watch_cpp(pid_t pid);

private:
	OJ_Info m_info;
};

#endif	//SANDBOX_H
