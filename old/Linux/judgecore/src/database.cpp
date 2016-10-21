#include "../include/database.h"

Database::Database(OJ_Info info)
{
	m_info  = info;
}

/*连接数据库*/
void Database::connect()
{
	try{
		if (false == m_conn.connect(Config::read("MYSQL_DATABASE_NAME").c_str(),
				Config::read("MYSQL_SERVER").c_str(),
			 	Config::read("MYSQL_USERNAME").c_str(),
			 	Config::read("MYSQL_PASSWORD").c_str()) ){  
			throw (OJ_ERROR)OJ_DATABASE_CON;
		}
	}catch(OJ_ERROR msg){
		throw;
	}
}


/*根据run_id和pro_id查询结果*/
void Database::queryinfo(OJ_Info &info)
{
	try{
		connect();

		//根据pro_id查询出 时间 和 空间限制
		string sql = "SELECT time_lim,mem_lim FROM " 
				+ Config::read("MYSQL_PROBLEM_TABLE") 
				+ " WHERE `pro_id` = "
				+ m_info.pro_id ;

		Query query = m_conn.query(sql);
		StoreQueryResult res;
		if (!(res = query.store()) || //如果有多重选择或者没有选择，都视为查询错误
			(1 != res.num_rows()) ){	
				throw (OJ_ERROR)OJ_DATABASE_QUERY;	
		}

		info.time_lim = atoi(res[0]["time_lim"].c_str());  
		info.mem_lim = atoi(res[0]["mem_lim"].c_str()); 
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
	 	connect();

		//根据run_id更新结果和运行信息
		//如果AC，信息内为时间和内存
		//如果为其他的，则不更新
		char str_time[128] = "0";
		char str_mem[128] = "0";
		if("AC" == str_res){	
			snprintf(str_time, 128, "%d", resinfo.time);
			snprintf(str_mem, 128, "%d", resinfo.memory);
		}

		string sql = "UPDATE `"
			+ Config::read("MYSQL_JUDGE_TABLE")
			+ "` SET `status` = '"+str_res
			+ " ',`time` = '" + (string)str_time
			+ " ',`memory` = '" + (string)str_mem
			+ " ' WHERE `run_id` = "
			+ m_info.run_id ;
		
		Query query = m_conn.query(sql);
		StoreQueryResult res;
		query.store();
	}catch(...){
		string message_judge = "run_id = "+m_info.run_id+"\nresult = 数据库访问错误";
		Log::log(Info_Log{
			LOG_ERROR,
			message_judge
		});

		throw (OJ_ERROR)OJ_SE;
	}
}

Database::~Database()
{

}