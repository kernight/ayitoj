/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git::http://git.ykgzs.com
*/
#ifndef CONST_H
#define CONST_H 

#include "head.h"

/*������Ϣ*/
struct OJ_Info
{
	string run_id;	//���б��
	string pro_id; 	//��Ŀ����
	string user_id; //�û�ID
	string title_in;//������������
	int time_lim; 	//ʱ������(ms)
	int mem_lim; 	//�ڴ�����(kb)
};

/*���ⷵ��ֵ*/
struct OJ_Reinfo
{
	OJ_ERROR msg;
	int time;
	int memory;
};

/*·���ַ���*/
const string PH_IO	= "data\\in2out\\";	//��������ļ���
const string PH_CODE= "data\\code\\";		//���뱣���ļ���
const string PH_RUN = "data\\running\\";	//���������ļ���
const string PH_LOG = "log\\core/";		//��־�����ļ���
const string PH_RES = "result.info";	//������
const string PH_CFG = "config\\core.cfg";//�����ļ�

/*ȫ�������ֵ�*/
extern map<string, string> Info_Config;

//���б��
extern string RUN_ID;

#endif //CONST_H