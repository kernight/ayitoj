#ifndef DATABASE_H
#define DATABASE_H 0

#include "head.h"

/*数据库模块
*/
class Database
{
public:
	Database(OJ_Info info);

	/*根据run_id和pro_id查询结果*/
	void queryinfo(OJ_Info &info);

	/*更新评测结果*/
	void updateresult(OJ_Reinfo resinfo);

	~Database();

private:
	/*执行sql语句*/
	bool Query(string sql);

private:
	OJ_Info m_info;
	MYSQL m_conn;
};

#endif //DATABASE_H