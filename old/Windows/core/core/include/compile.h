#ifndef COMPILE_H
#define COMPILE_H 0

/*�������ģ��*/

#include "head.h"

class Compile
{
public:
	Compile(OJ_Info info);
	~Compile(){};

	/*ִ��C/C++����*/
	int run_cpp();
private:
	OJ_Info m_info;
	
};

#endif	//COMPILE_H