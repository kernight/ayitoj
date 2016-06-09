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
		"���ݿ����Ӵ���"
	});
	}
}

/* ���ݴ�����״̬��ѯδ�������Ŀ */
void Database::queryinfo(queue<OJ_Info> &que_info)
{
	try{
		 //�����Ŷ�״̬��ѯ�� ÿ����¼ ��run_id �� pro_id
		string sql = "SELECT run_id,pro_id,user_id FROM " 
				+ Config::read("MYSQL_JUDGE_TABLE") 
				+ " WHERE `status` = 'WAIT' " ;

		if (true == Query(sql)){
			MYSQL_RES *res_set;
			MYSQL_ROW sql_row;

			res_set = mysql_store_result(&m_conn);    // ���ɽ����

			while (sql_row = mysql_fetch_row(res_set)){ //��˳���ȡÿһ�н����ϸ��Ϣ
				OJ_Info info;

				info.run_id = sql_row[0];
				info.pro_id = sql_row[1];
				info.user_id = sql_row[2];

				Log::log(Info_Log{
					LOG_NORMAL,
					"��⵽��¼ Runid = "+info.run_id
				});

				que_info.push(info);	//��ѯ����������

				//����״̬���ӵȴ�תΪ�������У�WAIT->Judging��
				string sql = "UPDATE `"
					+ Config::read("MYSQL_JUDGE_TABLE")
					+ "` SET `status` = 'Judging' WHERE `run_id` = "
					+ info.run_id;

				if (false == Query(sql)){
					Log::log(Info_Log{
						LOG_ERROR,
						"����ʧ�ܣ�"+info.run_id
					});
				}
			}

			mysql_free_result(res_set);//�ͷŽ����Դ 
		}
		
	}
	catch (OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"������¼ʱ��������"
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
			"���ݿ��ѯ���󡡣�"+sql
		});

		return false;
	}
}

Database::~Database()
{
	mysql_close(&m_conn);//�Ͽ�����  
}