#include "../include/database.h"

Database::Database()
{
	try{
		if (NULL == mysql_init(&m_conn)){
			throw (OJ_ERROR)OJ_DATABASE_CON;
		}

		if (NULL == mysql_real_connect(&m_conn,
			Config::read("MYSQL_SERVER").c_str(),
			Config::read("MYSQL_USERNAME").c_str(),
			//Config::read("MYSQL_PASSWORD").c_str(),
			"",
			Config::read("MYSQL_DATABASE_NAME").c_str(),
			3306,
			NULL,
			0)){
			throw (OJ_ERROR)OJ_DATABASE_CON;
		}
	}
	catch (OJ_ERROR){
		Log::log(Info_Log{
		LOG_ERROR,
		"数据库连接错误"
	});
	}
}

/* 根据待运行状态查询未评测的题目 */
void Database::queryinfo(queue<OJ_Info> &que_info)
{
	try{
		 //根据排队状态查询出 每条记录 的run_id 和 pro_id
		string sql = "SELECT run_id,pro_id,user_id FROM " 
				+ Config::read("MYSQL_JUDGE_TABLE") 
				+ " WHERE `status` = 'WAIT' " ;

		if (true == Query(sql)){
			MYSQL_RES *res_set;
			MYSQL_ROW sql_row;

			res_set = mysql_store_result(&m_conn);    // 生成结果集

			while (sql_row = mysql_fetch_row(res_set)){ //按顺序获取每一行结果详细信息
				OJ_Info info;

				info.run_id = sql_row[0];
				info.pro_id = sql_row[1];
				info.user_id = sql_row[2];

				Log::log(Info_Log{
					LOG_NORMAL,
					"检测到记录 Runid = "+info.run_id
				});

				que_info.push(info);	//查询结果进入队列

				//更新状态，从等待转为正在评判（WAIT->Judging）
				string sql = "UPDATE `"
					+ Config::read("MYSQL_JUDGE_TABLE")
					+ "` SET `status` = 'Judging' WHERE `run_id` = "
					+ info.run_id;

				if (false == Query(sql)){
					Log::log(Info_Log{
						LOG_ERROR,
						"更新失败："+info.run_id
					});
				}
			}

			mysql_free_result(res_set);//释放结果资源 
		}
		
	}
	catch (OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"操作记录时发生错误"
		});
	}
}

bool Database::Query(string sql)
{
	try{

		if (mysql_query(&m_conn, sql.c_str())){
			throw (OJ_ERROR)OJ_DATABASE_QUERY; //数据库查询失败（查询失败）
		}

		return true;
	}
	catch (OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"数据库查询错误　："+sql
		});

		return false;
	}
}

Database::~Database()
{
	mysql_close(&m_conn);//断开连接  
}