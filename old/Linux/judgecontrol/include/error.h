/*Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
*/

/*�쳣�붨��*/
#ifndef ERROR_H
#define ERROR_H

/*OJ�쳣����*/
typedef long long OJ_ERROR;

/*OJ���д�����*/
enum OJ_RUN_ERROR
{
	OJ_ERROR_NULL = 0,	//�޴���
	OJ_SYSTEM = 1000,	//ϵͳ����
	OJ_CONFIG_OPEN 
		= 2000, 	//�����ļ����쳣
	OJ_LOG_FILE,		//��־�ļ��򿪲�����
	OJ_DATABASE_CON,	//�������ݿ�ʧ��
	OJ_DATABASE_QUERY,	//��ѯʧ��
	OJ_FILE_NONE,		//û���ļ������ļ���
	OJ_FILE_DIR,		//�л�Ŀ¼ʧ��
};

#endif // ERROR_H
