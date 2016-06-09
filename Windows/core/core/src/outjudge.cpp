#include "../include/outjudge.h"

Outjudge::Outjudge(OJ_Info info)
{
	m_info = info;
	string path_run = PH_RUN + RUN_ID + "\\";
	m_filename = path_run + m_info.title_in + ".out";
	m_nsfilename = path_run + m_info.title_in + "-ns.out";
}

int Outjudge::tons()
{
	ifstream fin;
	ofstream fout;
	try{
		fin.open(m_filename);
		fout.open(m_nsfilename);
		if(false == fin.is_open()){
			throw (OJ_ERROR) OJ_SE;
		}
		if(false == fout.is_open()){
			throw (OJ_ERROR) OJ_SE;
		}
		char word = '\0';
		//消除空格、制表符和换行
		while(fin>>word){
			if(' ' == word &&
				'\n' == word &&
				'\r' == word &&
				'\t' == word){
				continue;
			}else{
				fout << word;
			}
		}
		cout << endl;

		fin.close();
		fout.close();
	}catch(OJ_ERROR msg){
		Log::log(Info_Log{
			LOG_ERROR,
			"无符号文件转存出错"
		});
		fin.close();
		fout.close();
		throw ;
	}

	
	return -1;
}

int Outjudge::nsjudge()
{
	FILE *fp_cmd = NULL;
	string path_ns_answer = PH_IO + m_info.pro_id + "\\" + m_info.title_in + "-ns.out";
	try{
		
		if (false == file_cmp(path_ns_answer, m_nsfilename)){
			throw (OJ_ERROR)OJ_WA;
		}

	}catch(OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"无符号结果文件对比失败：" + path_ns_answer + " " + m_nsfilename
		});
		throw ;
	}
	
	return 0;
}

int Outjudge::judge()
{
	FILE *fp_cmd = NULL;
	try{
		string path_answer = PH_IO + m_info.pro_id + "\\" + m_info.title_in + ".out";

		if (false == file_cmp(path_answer, m_filename)){
			throw (OJ_ERROR)OJ_PE;
		}
	
	}catch(OJ_ERROR msg){
		Log::log(Info_Log{
			LOG_ERROR,
			"结果文件对比失败"
		});
		throw ;
	}
	return 0;
}