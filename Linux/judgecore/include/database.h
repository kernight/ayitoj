#ifndef DATABASE_H
#define DATABASE_H 0

#include "head.h"

using namespace mysqlpp;

/*数据库模块
*/
class Database
{
public:
	Database(OJ_Info info);

	/*连接数据库*/
	void connect();

	/*根据run_id和pro_id查询结果*/
	void queryinfo(OJ_Info &info);

	/*更新评测结果*/
	void updateresult(OJ_Reinfo resinfo);

	~Database();

private:
	OJ_Info m_info;
	Connection m_conn; 
};

#endif //DATABASE_H