/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/
#ifndef LOG_H
#define LOG_H 

#include "head.h"

/*日志信息分级*/
enum Log_Level
{
	LOG_ERROR=0,	//错误
	LOG_JUDGE,	//判定数据
	LOG_NORMAL,	//正常
};

/*日志信息类*/
class Info_Log{
public:
	/*初始化日志信息*/
	Info_Log(int pri, string datail_info);

	friend ostream & operator <<(ostream &out,Info_Log info);
	friend bool operator <(Info_Log info_a, Info_Log info_b);

public:
	int m_priori;	//优先级
	string m_detail;	//详细信息
	string m_date;	//发生日期
	string m_time;	//发生时间
};

/*日志文件操作类*/
class Log
{
public:
	/*添加记录*/
	static OJ_ERROR log(Info_Log info);

	/*针对记录进行特殊操作，比如系统异常报警机制等等*/
	static OJ_ERROR action(Info_Log info);

	/*保存日志到文件*/
	static OJ_ERROR save();
};

#endif //LOG_H