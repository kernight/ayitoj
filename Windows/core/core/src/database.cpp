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
		"���ݿ����Ӵ���"
	});
	}
}


bool Database::Query(string sql)
{
	try{

		if (mysql_query(&m_conn, sql.c_str())){
			throw (OJ_ERROR)OJ_DATABASE_QUERY; //���ݿ��ѯʧ�ܣ���ѯʧ�ܣ�
		}

		return true;
	}
	catch (OJ_ERROR){
		Log::log(Info_Log{
		LOG_ERROR,
		"���ݿ��ѯ����"
	});

		return false;
	}
}

/*����run_id��pro_id��ѯ���*/
void Database::queryinfo(OJ_Info &info)
{
	try{
		//����pro_id��ѯ�� ʱ�� �� �ռ�����
		string sql = "SELECT time_lim,mem_lim FROM " 
				+ Config::read("MYSQL_PROBLEM_TABLE") 
				+ " WHERE `pro_id` = "
				+ m_info.pro_id ;

		if (true == Query(sql)){
			MYSQL_RES *res_set;
			MYSQL_ROW sql_row;

			res_set = mysql_store_result(&m_conn);    // ���ɽ����

			while (sql_row = mysql_fetch_row(res_set)){ //��˳���ȡÿһ�н����ϸ��Ϣ
				info.time_lim = atoi(sql_row[0]);
				info.mem_lim = atoi(sql_row[1]);
			}
		}

		
	}catch(...){
		string message_judge = "run_id = "+m_info.run_id+"\nresult = ���ݿ���ʴ���";

		Log::log(Info_Log{
			LOG_ERROR,
			message_judge
		});

		throw (OJ_ERROR)OJ_SE;
	}
}

/*����������*/
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

	cout<<"������ = "<<str_res<<endl;
	 try{

		//����run_id���½����������Ϣ
		//���AC����Ϣ��Ϊʱ����ڴ�
		//���Ϊ�����ģ��򲻸���
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
			"������³���"
		});

		throw (OJ_ERROR)OJ_SE;
	}
}

Database::~Database()
{
	mysql_close(&m_conn);//�Ͽ�����  
}