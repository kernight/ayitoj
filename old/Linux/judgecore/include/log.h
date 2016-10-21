/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/
#ifndef LOG_H
#define LOG_H 

#include "head.h"

/*��־��Ϣ�ּ�*/
enum Log_Level
{
	LOG_ERROR=0,	//����
	LOG_JUDGE,	//�ж�����
	LOG_NORMAL,	//����
};

/*��־��Ϣ��*/
class Info_Log{
public:
	/*��ʼ����־��Ϣ*/
	Info_Log(int pri, string datail_info);

	friend ostream & operator <<(ostream &out,Info_Log info);
	friend bool operator <(Info_Log info_a, Info_Log info_b);

public:
	int m_priori;	//���ȼ�
	string m_detail;	//��ϸ��Ϣ
	string m_date;	//��������
	string m_time;	//����ʱ��
};

/*��־�ļ�������*/
class Log
{
public:
	/*��Ӽ�¼*/
	static OJ_ERROR log(Info_Log info);

	/*��Լ�¼�����������������ϵͳ�쳣�������Ƶȵ�*/
	static OJ_ERROR action(Info_Log info);

	/*������־���ļ�*/
	static OJ_ERROR save();
};

#endif //LOG_H