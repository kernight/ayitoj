#ifndef OUTJUDGE_H
#define OUTJUDGE_H 0

/*
*����ж�ģ�飬�жϳ����������Ƿ���ȷ
*/

#include "head.h"

class Outjudge
{
public:
	/*��ȡ����ļ�
	string num ���б��
	*/
	Outjudge(OJ_Info info);

	~Outjudge(){};
	
	/*���ļ�ת��Ϊ�޿ո�汾*/
	int tons();

	/*�޷��ż��*/
	int nsjudge();

	/*���ռ��*/
	int judge();

private:
	/*����ļ���*/
	string m_filename;

	/*�޷��Ž���ļ���*/
	string m_nsfilename;
	
	/*������Ϣ*/
	OJ_Info m_info;
};

#endif //OUTJUDGE_H