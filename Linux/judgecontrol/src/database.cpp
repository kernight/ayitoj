#include "../include/database.h"

Database::Database()
{
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
		cerr<<"数据库访问错误"<<endl;
		Log::log(Info_Log{
			LOG_ERROR,
			"数据库访问错误"
		});
	}
}


/*根据待运行状态查询未评测的题目*/
void Database::queryinfo(queue<OJ_Info> &que_info)
{
	try{
		connect();

		 //根据排队状态查询出 每条记录 的run_id 和 pro_id
		string sql = "SELECT run_id,pro_id,user_id FROM " 
				+ Config::read("MYSQL_JUDGE_TABLE") 
				+ " WHERE `status` = 'WAIT' " ;

		Query query = m_conn.query(sql);
		StoreQueryResult res;
		if (!(res = query.store())){	
			cerr<<"查询失败"<<endl;
			throw (OJ_ERROR)OJ_DATABASE_QUERY;	
		}
		int num = res.num_rows();
		if(0 != num){
			cout<<"查到的数目为:"<<num<<endl;
		}
		
		for(int i = 0; i < num; i++){
			OJ_Info info;
			cout<<"run_id = "<<res[i]["run_id"]<<endl;
			info.run_id = res[i]["run_id"].c_str();  
			info.pro_id = res[i]["pro_id"].c_str();
			info.user_id =  res[i]["user_id"].c_str();
				
			que_info.push(info);	//查询结果进入队列

			string sql = "UPDATE `"
				+ Config::read("MYSQL_JUDGE_TABLE")
				+ "` SET `result` = 'Judging' WHERE `run_id` = "
				+ info.run_id ;
			
			Query query = m_conn.query(sql);
			StoreQueryResult res;
			query.store();	//更新运行状态

			// Log::log(Info_Log{
			// 	LOG_NORMAL,
			// 	"数据库信息采集。 run_id = " + res[i]["run_id"]
			// });
		}

	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"系统发生错误"
		});
	}
}

Database::~Database()
{

}