/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/

/*异常码定义*/
#ifndef ERROR_H
#define ERROR_H

/*OJ异常类型*/
typedef long long OJ_ERROR;

/*OJ评测错误描述码*/
enum OJ_JUDGE_ERROR
{
	OJ_AC = 1000,	//Accepted 		正确
	OJ_WA,		//Wrong Answer 	答案错误
	OJ_PE,		//Presenation Error 	格式错误
	OJ_RE,		//Runtime Error 	运行出错
	OJ_PF,		//Restricted Function 	使用被限制的函数
	OJ_TLE,		//Time Limit Exceeded 	时间超限
	OJ_MLE,		//Memory Limit Exceeded 	内存超限
	OJ_OLE,		//Output Limit Exceeded 	输出超限
	OJ_CE,		//Compile Error 	编译出错
	OJ_SE,		//System Error 	系统出错
};

/*OJ运行错误码*/
enum OJ_RUN_ERROR
{
	OJ_ERROR_NULL = 0,	//无错误
	OJ_CONFIG_OPEN 
		= 2000, 	//配置文件打开异常
	OJ_LOG_FILE,		//日志文件打开不正常
	OJ_DATABASE_CON,	//连接数据库失败
	OJ_DATABASE_QUERY,	//查询失败
	OJ_FILE_NONE,		//没有文件或者文件夹
	OJ_FILE_DIR,		//切换目录失败
};

#endif // ERROR_H
