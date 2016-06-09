/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/

#include "../include/config.h"

map<string, string> Info_Config;

/*�����ļ�·��*/
static string m_path;

/*ָ�������ļ���ַ*/
void Config::setpath(string path)
{
	m_path = path;
}

/*��������*/
OJ_ERROR Config::load()
{
	ifstream fin(m_path.c_str());
	
	try {
		if (false == fin.is_open()) {
			throw (OJ_ERROR) OJ_CONFIG_OPEN;
		}

		Log::log(Info_Log{LOG_NORMAL, "���ļ����������ļ�"});
		
		string key = "";
		string value = "";
		while (fin >> key) {
			/*�����ȡ���Σ������м��Ǹ��Ⱥ�*/
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

		Log::log(Info_Log{LOG_ERROR, "�����ļ�����ʧ��"});
		throw (OJ_ERROR) INFO;
	}
	return OJ_ERROR_NULL;
}

/*�޸�����*/
OJ_ERROR Config::change(string key, string value)
{
	ofstream fout(m_path.c_str());

	try {
		if (false == fout.is_open()) {
			throw (OJ_ERROR) OJ_CONFIG_OPEN;
		}

		Log::log(Info_Log{ LOG_NORMAL, "�޸������ļ����޸���[ "+key+" ],�޸�ֵ[ "+value+" ]"});

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

		Log::log(Info_Log{LOG_ERROR, "�����ļ��޸�ʧ��"});
		throw (OJ_ERROR) INFO;
	}
	return OJ_ERROR_NULL;
}

/*��ȡĳ������ �ַ���*/
string Config::read(string key)
{
	return Info_Config[key];
}

/*��ȡĳ������ ����*/
int Config::read(string key,string style)
{
	return atoi(Info_Config[key].c_str());
}