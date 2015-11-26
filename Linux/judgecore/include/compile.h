#ifndef COMPILE_H
#define COMPILE_H 0

/*程序编译模块*/

#include "head.h"

class Compile
{
public:
	Compile(OJ_Info info);
	~Compile(){};

	/*执行C/C++编译*/
	int run_cpp();
private:
	OJ_Info m_info;
	
};

const string complie_data[0]="g++ %s.cc -o %s -O2 -Wall -std=c99 -lm --static ";

#endif	//COMPILE_H