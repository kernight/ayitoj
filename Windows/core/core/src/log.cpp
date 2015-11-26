/* Author:steve-liu
*blog:http://blog.csdn.net/liuxucoder/
*git:https://code.csdn.net/youqi1shi/guanjia
 */

#include "../include/log.h"

/* 字符串流，用来格式化时间信息 */
stringstream string_stream;

/* 日志消息优先队列 */
priority_queue<Info_Log> Que_Log;

/* 初始化日志信息 */
Info_Log::Info_Log(int pri, string datail_info)
{
	m_priori = pri;
	m_detail = datail_info;

	time_t now = time(NULL);
	tm *tm_now = new tm;
	localtime_s(tm_now, &now);
	string temp = "";

	/* 格式化日期信息 */
	string_stream.clear();
	string_stream<<tm_now->tm_year+1900<<" "
					<<tm_now->tm_mon+1<<" "
					<<tm_now->tm_mday;
	
	m_date = "";
	while (string_stream >> temp){
		m_date += temp;
		m_date += "-";
	}
	m_date[m_date.length()-1]='\0';


	/* 格式化时间信息 */
	string_stream.clear();
	string_stream << tm_now->tm_hour << " "
					<< tm_now->tm_min << " "
					<< tm_now->tm_sec;
	m_time = "";
	while (string_stream >> temp){
		m_time += temp;
		m_time += ":";
	}
	m_time[m_time.length() - 1] = '\0';

	delete(tm_now);
	tm_now = NULL;
}

ostream & operator <<(ostream &out,Info_Log info)
{
	out << "[ Date ] : " <<info.m_date << "[ Time ] : " << info.m_time << endl;
	out << "[ Info ] : " << info.m_detail << endl;
	out << endl;

	return out;
}

bool operator <(Info_Log info_a, Info_Log info_b)
{
	return info_a.m_priori < info_b.m_priori;
}



/* 添加记录 */ 
OJ_ERROR Log::log(Info_Log info)
{
	Que_Log.push(info);

	action(info);

	save();

	return OJ_ERROR_NULL;
}

/* 针对记录进行特殊操作，比如系统异常报警机制等等 */
OJ_ERROR Log::action(Info_Log info)
{
	return OJ_ERROR_NULL;
}

/* 保存日志到文件 */
OJ_ERROR Log::save()
{
	while (false == Que_Log.empty())
	{
		Info_Log info = Que_Log.top();
		Que_Log.pop();

		string file_name = "";
		if (LOG_ERROR == info.m_priori){
			file_name += PH_LOG+"/Error - ";
		}
		else{
			file_name += PH_LOG+"/Normal-";
		}

		file_name = file_name + RUN_ID + ".log";

		ofstream fout(file_name.c_str(), ios::app);
		try{
			cout << info << endl;

			if (false == fout.is_open()){
				throw (OJ_ERROR)OJ_LOG_FILE;
			}

			fout << info;

			fout.close();
		}
		catch (OJ_ERROR INFO){
			if(OJ_LOG_FILE == INFO){
				cerr << "日志文件打开不正常" << endl;
				fout.close();
			}
		}
	}

	return OJ_ERROR_NULL;
}