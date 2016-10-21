#ifndef OUTJUDGE_H
#define OUTJUDGE_H 0

/*
*结果判定模块，判断程序输出结果是否正确
*/

#include "head.h"

class Outjudge
{
public:
	/*获取结果文件
	string num 运行编号
	*/
	Outjudge(OJ_Info info);

	~Outjudge(){};
	
	/*把文件转换为无空格版本*/
	int tons();

	/*无符号检测*/
	int nsjudge();

	/*最终检测*/
	int judge();

private:
	/*结果文件名*/
	string m_filename;

	/*无符号结果文件名*/
	string m_nsfilename;
	
	/*评测信息*/
	OJ_Info m_info;
};

#endif //OUTJUDGE_H