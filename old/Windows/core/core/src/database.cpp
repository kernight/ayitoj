#include "../include/database.h"

Database::Database(OJ_Info info)
{
	m_info  = info;
	try{
		if (NULL == mysql_init(&m_conn)){
			throw (OJ_ERROR)OJ_DATABASE_CON;
		}

		if (NULL == mysql_real_connect(&m_conn,
			Config::read("MYSQL_SERVER").c_str(),
			"root",
			Config::read("MYSQL_PASSWORD").c_str(),
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
		"数据库查询错误"
	});

		return false;
	}
}

/*根据run_id和pro_id查询结果*/
void Database::queryinfo(OJ_Info &info)
{
	try{
		//根据pro_id查询出 时间 和 空间限制
		string sql = "SELECT time_lim,mem_lim FROM " 
				+ Config::read("MYSQL_PROBLEM_TABLE") 
				+ " WHERE `pro_id` = "
				+ m_info.pro_id ;

		if (true == Query(sql)){
			MYSQL_RES *res_set;
			MYSQL_ROW sql_row;

			res_set = mysql_store_result(&m_conn);    // 生成结果集

			while (sql_row = mysql_fetch_row(res_set)){ //按顺序获取每一行结果详细信息
				info.time_lim = atoi(sql_row[0]);
				info.mem_lim = atoi(sql_row[1]);
			}
		}

		
	}catch(...){
		string message_judge = "run_id = "+m_info.run_id+"\nresult = 数据库访问错误";

		Log::log(Info_Log{
			LOG_ERROR,
			message_judge
		});

		throw (OJ_ERROR)OJ_SE;
	}
}

/*更新评测结果*/
void Database::updateresult(OJ_Reinfo resinfo)
{
	string str_res = "";
	switch(resinfo.msg)
	{
		case OJ_AC:
			str_res = "AC";
			break;
		case OJ_WA:
			str_res = "WA";
			break;
		case OJ_CE:
			str_res = "CE";
			break;
		case OJ_PE:
			str_res = "PE";
			break;
		case OJ_RE:
			str_res = "RE";
			break;
		case OJ_PF:
			str_res = "PF";
			break;
		case OJ_MLE:
			str_res = "MLE";
			break;
		case OJ_OLE:
			str_res = "OLE";
			break;
		case OJ_TLE:
			str_res = "TLE";
			break;
		default:
			str_res = "SE";
			break;
	}

	cout<<"评测结果 = "<<str_res<<endl;
	 try{

		//根据run_id更新结果和运行信息
		//如果AC，信息内为时间和内存
		//如果为其他的，则不更新
		char str_time[128] = "0";
		char str_mem[128] = "0";
		if("AC" == str_res){	
			_snprintf_s(str_time, 128, "%d", resinfo.time);
			_snprintf_s(str_mem, 128, "%d", resinfo.memory);
		}

		string sql = "UPDATE `"
			+ Config::read("MYSQL_JUDGE_TABLE")
			+ "` SET `status` = '"+str_res
			+ " ',`time` = '" + (string)str_time
			+ " ',`memory` = '" + (string)str_mem
			+ " ' WHERE `run_id` = "
			+ m_info.run_id ;
		
		if (false == Query(sql)){
			throw (OJ_ERROR)OJ_DATABASE_QUERY;
		}
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"结果更新出错"
		});

		throw (OJ_ERROR)OJ_SE;
	}
}

Database::~Database()
{
	mysql_close(&m_conn);//断开连接  
}