/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/

/*�쳣�붨��*/
#ifndef ERROR_H
#define ERROR_H

/*OJ�쳣����*/
typedef long long OJ_ERROR;

/*OJ�������������*/
enum OJ_JUDGE_ERROR
{
	OJ_AC = 1000,	//Accepted 		��ȷ
	OJ_WA,		//Wrong Answer 	�𰸴���
	OJ_PE,		//Presenation Error 	��ʽ����
	OJ_RE,		//Runtime Error 	���г���
	OJ_PF,		//Restricted Function 	ʹ�ñ����Ƶĺ���
	OJ_TLE,		//Time Limit Exceeded 	ʱ�䳬��
	OJ_MLE,		//Memory Limit Exceeded 	�ڴ泬��
	OJ_OLE,		//Output Limit Exceeded 	�������
	OJ_CE,		//Compile Error 	�������
	OJ_SE,		//System Error 	ϵͳ����
};

/*OJ���д�����*/
enum OJ_RUN_ERROR
{
	OJ_ERROR_NULL = 0,	//�޴���
	OJ_CONFIG_OPEN 
		= 2000, 	//�����ļ����쳣
	OJ_LOG_FILE,		//��־�ļ��򿪲�����
	OJ_DATABASE_CON,	//�������ݿ�ʧ��
	OJ_DATABASE_QUERY,	//��ѯʧ��
	OJ_FILE_NONE,		//û���ļ������ļ���
	OJ_FILE_DIR,		//�л�Ŀ¼ʧ��
};

#endif // ERROR_H
