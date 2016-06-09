/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/
#ifndef CONFIG_H
#define CONFIG_H 

#include "head.h"

/*�����ļ�������*/
class Config
{
public:
	/*���������ļ�·��*/
	static void setpath(string path);

	/*���ļ��м�������*/
	static OJ_ERROR load();

	/*�޸Ļ�����ĳ������*/
	static OJ_ERROR change(string key, string value);

	/*��ȡĳ������ �ַ���*/
	static string read(string key);
	
	/*��ȡĳ������ ����*/
	static int read(string key, string style);
};

#endif //CONFIG_H