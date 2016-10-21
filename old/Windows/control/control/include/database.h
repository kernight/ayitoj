#ifndef DATABASE_H
#define DATABASE_H 0

#include "head.h"

/*
数据库模块
*/
class Database
{
public:
	Database();

	/* 根据待运行状态查询未评测的题目 */
	void queryinfo(queue<OJ_Info> &que_info);

	~Database();

private:
	/*执行sql语句*/
	bool Query(string sql);
private:
	OJ_Info m_info;
	MYSQL  m_conn;
};

#endif //DATABASE_H