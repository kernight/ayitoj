#ifndef DATABASE_H
#define DATABASE_H 0

#include "head.h"

/*
���ݿ�ģ��
*/
class Database
{
public:
	Database();

	/* ���ݴ�����״̬��ѯδ�������Ŀ */
	void queryinfo(queue<OJ_Info> &que_info);

	~Database();

private:
	/*ִ��sql���*/
	bool Query(string sql);
private:
	OJ_Info m_info;
	MYSQL  m_conn;
};

#endif //DATABASE_H