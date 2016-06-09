/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/
#ifndef CONFIG_H
#define CONFIG_H 

#include "head.h"

/*配置文件操作类*/
class Config
{
public:
	/*设置配置文件路径*/
	static void setpath(string path);

	/*从文件中加载配置*/
	static OJ_ERROR load();

	/*修改或增加某项配置*/
	static OJ_ERROR change(string key, string value);

	/*读取某项配置 字符串*/
	static string read(string key);
	
	/*读取某项配置 整数*/
	static int read(string key, string style);
};

#endif //CONFIG_H