/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/

/*异常码定义*/
#ifndef ERROR_H
#define ERROR_H

/*OJ异常类型*/
typedef long long OJ_ERROR;

/*OJ运行错误码*/
enum OJ_RUN_ERROR
{
	OJ_ERROR_NULL = 0,	//无错误
	OJ_SYSTEM = 1000,	//系统出错
	OJ_CONFIG_OPEN 
		= 2000, 	//配置文件打开异常
	OJ_LOG_FILE,		//日志文件打开不正常
	OJ_DATABASE_CON,	//连接数据库失败
	OJ_DATABASE_QUERY,	//查询失败
	OJ_FILE_NONE,		//没有文件或者文件夹
	OJ_FILE_DIR,		//切换目录失败
};

#endif // ERROR_H
