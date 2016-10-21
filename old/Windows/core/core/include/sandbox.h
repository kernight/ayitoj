#ifndef SANDBOX_H
#define SANDBOX_H 0

/*ɳ������ģ��*/

#include "head.h"

#define STD_KB 1024
#define STD_MB (1024*1024)
#define BUFFER_SIZE 1024

class Sandbox
{
public:
	Sandbox(OJ_Info info);
	~Sandbox(){};

	/*C/C++����*/
	OJ_Reinfo cpp();

	/*�ӽ�������C/C++����*/
	PROCESS_INFORMATION run_cpp();

	/*
	*���C/C++�����������
	*DWORD pid �ӽ���id
	*/
	OJ_Reinfo watch_cpp(PROCESS_INFORMATION pi);

private:
	OJ_Info m_info;
};

#endif	//SANDBOX_H
