#ifndef COMPILE_H
#define COMPILE_H 0

/*≥Ã–Ú±‡“Îƒ£øÈ*/

#include "head.h"

class Compile
{
public:
	Compile(OJ_Info info);
	~Compile(){};

	/*÷¥––C/C++±‡“Î*/
	int run_cpp();
private:
	OJ_Info m_info;
	
};

#endif	//COMPILE_H