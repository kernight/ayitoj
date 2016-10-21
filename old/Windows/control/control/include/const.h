/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/
#ifndef CONST_H
#define CONST_H 

#include "head.h"

/*评测信息*/
struct OJ_Info
{
	string run_id;	 //运行编号
	string pro_id; 	//题目号码
	string user_id; 	//用户ID
	string str_code; //用户提交的代码
};

/*路径字符串*/
const string PH_RUNNING = "data\\running\\";//代码保存目录
const string PH_LOG = "log\\control\\";		//日志评测文件夹
const string PH_CORE = "core.exe";			//评测机路径
const string PH_CFG = "config/control.cfg";	//配置文件

#define BUFFER_SIZE 1024

/*全局配置字典*/
extern map<string, string> Info_Config;

#endif //CONST_H