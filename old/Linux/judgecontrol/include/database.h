#ifndef DATABASE_H
#define DATABASE_H 0

#include "head.h"

using namespace mysqlpp;

/*数据库模块
*/
class Database
{
public:
	Database();

	/*连接数据库*/
	void connect();

	/*根据待运行状态查询未评测的题目*/
	void queryinfo(queue<OJ_Info> &que_info);

	~Database();

private:
	OJ_Info m_info;
	Connection m_conn; 
};

#endif //DATABASE_H