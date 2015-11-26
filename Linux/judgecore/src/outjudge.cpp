#include "../include/outjudge.h"

Outjudge::Outjudge(OJ_Info info)
{
	m_info = info;
	m_filename     = m_info.pro_id + "-" + m_info.title_in + ".out";
	m_nsfilename = m_info.pro_id  + "-" + m_info.title_in + "-ns" + ".out";
}

int Outjudge::tons()
{
	ifstream fin(m_filename.c_str());
	ofstream fout(m_nsfilename.c_str());
	try{
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
				fout<<word;
			}
		}
	}catch(OJ_ERROR msg){
		cerr<<"无符号文件转存出错"<<endl;
		fin.close();
		fout.close();
		throw ;
	}

	fin.close();
	fout.close();
	return -1;
}

int Outjudge::nsjudge()
{
	FILE *fp_cmd = NULL;
	try{
		string path_ns_answer = "../../" + PH_IO+m_info.pro_id+"/"+m_info.title_in+"-ns.out";
		string cmd = "diff "+path_ns_answer+" "+m_nsfilename;

		fp_cmd = popen(cmd.c_str(), "r");
		if(NULL == fp_cmd){
			cout<<cmd<<endl;
			throw (OJ_ERROR) OJ_SE;
		}

		char tmp[1024]; //设置一个合适的长度，以存储每一行输出
		if (NULL != fgets(tmp, sizeof(tmp), fp_cmd) ) {
			throw (OJ_ERROR) OJ_WA;
		}

		pclose(fp_cmd);
	}catch(OJ_ERROR msg){
		cerr<<"无符号结果文件对比失败"<<endl;
		if(OJ_SE == msg){
			pclose(fp_cmd);
		}
		throw ;
	}
	
	return 0;
}

int Outjudge::judge()
{
	FILE *fp_cmd = NULL;
	try{
		string path_answer = "../../" + PH_IO+m_info.pro_id+"/"+m_info.title_in+".out";
		string cmd = "diff "+path_answer+" "+m_filename;

		fp_cmd = popen(cmd.c_str(), "r");

		if(NULL == fp_cmd){
			throw (OJ_ERROR) OJ_SE;
		}

		char tmp[1024]; //设置一个合适的长度，以存储每一行输出
		if (fgets(tmp, sizeof(tmp), fp_cmd) != NULL) {
			throw (OJ_ERROR) OJ_PE;
		}

		pclose(fp_cmd);		
	}catch(OJ_ERROR msg){
		cerr<<"结果文件对比失败"<<endl;
		if(OJ_SE == msg){
			pclose(fp_cmd);
		}
		throw ;
	}
	return 0;
}