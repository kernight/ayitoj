/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/

#include "../include/config.h"

map<string, string> Info_Config;

/*配置文件路径*/
static string m_path;

/*指定配置文件地址*/
void Config::setpath(string path)
{
	m_path = path;
}

/*加载配置*/
OJ_ERROR Config::load()
{
	ifstream fin(m_path.c_str());
	
	try {
		if (false == fin.is_open()) {
			throw (OJ_ERROR) OJ_CONFIG_OPEN;
		}

		Log::log(Info_Log{LOG_NORMAL, "从文件加载配置文件"});
		
		string key = "";
		string value = "";
		while (fin >> key) {
			/*这里读取两次，消除中间那个等号*/
			fin >> value >> value;
			if ("^"== value){
				value = "";
			}
			Info_Config[key] = value;	
		}

		fin.close();
	}
	catch (OJ_ERROR INFO) {
		if (OJ_CONFIG_OPEN == INFO){
			fin.close();
		}

		Log::log(Info_Log{LOG_ERROR, "配置文件加载失败"});
		throw (OJ_ERROR) INFO;
	}
	return OJ_ERROR_NULL;
}

/*修改配置*/
OJ_ERROR Config::change(string key, string value)
{
	ofstream fout(m_path.c_str());

	try {
		if (false == fout.is_open()) {
			throw (OJ_ERROR) OJ_CONFIG_OPEN;
		}

		Log::log(Info_Log{ LOG_NORMAL, "修改配置文件。修改项[ "+key+" ],修改值[ "+value+" ]"});

		Info_Config[key] = value;

		map<string, string>::iterator pos;
		for (pos = Info_Config.begin(); pos != Info_Config.end(); pos++){
			fout << pos->first << " = " << pos->second << endl;
		}

		fout.close();
	}
	catch (OJ_ERROR INFO) {
		if (OJ_CONFIG_OPEN == INFO){
			fout.close();
		}

		Log::log(Info_Log{LOG_ERROR, "配置文件修改失败"});
		throw (OJ_ERROR) INFO;
	}
	return OJ_ERROR_NULL;
}

/*获取某项配置 字符串*/
string Config::read(string key)
{
	return Info_Config[key];
}

/*获取某项配置 整数*/
int Config::read(string key,string style)
{
	return atoi(Info_Config[key].c_str());
}