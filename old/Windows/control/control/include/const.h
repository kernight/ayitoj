/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:http://git.ykgzs.com
*/
#ifndef CONST_H
#define CONST_H 

#include "head.h"

/*������Ϣ*/
struct OJ_Info
{
	string run_id;	 //���б��
	string pro_id; 	//��Ŀ����
	string user_id; 	//�û�ID
	string str_code; //�û��ύ�Ĵ���
};

/*·���ַ���*/
const string PH_RUNNING = "data\\running\\";//���뱣��Ŀ¼
const string PH_LOG = "log\\control\\";		//��־�����ļ���
const string PH_CORE = "core.exe";			//�����·��
const string PH_CFG = "config/control.cfg";	//�����ļ�

#define BUFFER_SIZE 1024

/*ȫ�������ֵ�*/
extern map<string, string> Info_Config;

#endif //CONST_H