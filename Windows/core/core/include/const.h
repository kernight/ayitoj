/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git::http://git.ykgzs.com
*/
#ifndef CONST_H
#define CONST_H 

#include "head.h"

/*评测信息*/
struct OJ_Info
{
	string run_id;	//运行编号
	string pro_id; 	//题目号码
	string user_id; //用户ID
	string title_in;//输入数据名称
	int time_lim; 	//时间限制(ms)
	int mem_lim; 	//内存限制(kb)
};

/*评测返回值*/
struct OJ_Reinfo
{
	OJ_ERROR msg;
	int time;
	int memory;
};

/*路径字符串*/
const string PH_IO	= "data\\in2out\\";	//输入输出文件夹
const string PH_CODE= "data\\code\\";		//代码保存文件夹
const string PH_RUN = "data\\running\\";	//代码评测文件夹
const string PH_LOG = "log\\core/";		//日志评测文件夹
const string PH_RES = "result.info";	//评测结果
const string PH_CFG = "config\\core.cfg";//配置文件

/*全局配置字典*/
extern map<string, string> Info_Config;

//运行编号
extern string RUN_ID;

#endif //CONST_H