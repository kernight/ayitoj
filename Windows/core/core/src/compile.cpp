#include "../include/compile.h"

Compile::Compile(OJ_Info info)
{
	m_info = info;
}

int Compile::run_cpp()
{
	try{
		string path_run = PH_RUN + RUN_ID + "\\";
		string path_ceinfo = path_run + PH_RES;/*������Ϣ�ļ�·��*/
		
		if (0 == get_file_size((path_run + "Main.cpp").c_str())){
			Log::log(Info_Log{
				LOG_ERROR,
				"�����ļ�������"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		//������ʱ��������,��������Ŀ¼�Ž�ȥ
		char curr_path[1024];//��ǰ����Ŀ¼
		GetCurrentDirectory(1024, curr_path);

		char *path = getenv("Path");//��������
		if (NULL == path){
			Log::log(Info_Log{
				LOG_ERROR,
				"����������ȡ����"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		string PathShell = "Path=" + (string)path + ';' + curr_path +"\\"+ Config::read("COMPILE_PATH");
		Log::log(Info_Log{
			LOG_NORMAL,
			"��������" + PathShell
		});
		if (0 != putenv(PathShell.c_str())){
			Log::log(Info_Log{
				LOG_ERROR,
				"�����������ô���"
			});
			throw (OJ_ERROR)OJ_SE;
		}
		
		string cmd = "g++ "+ path_run + "Main.cpp -o " + path_run + "Main -O2 -w -lm --static";

		if (false == my_exec(cmd, path_ceinfo, 10)){
			Log::log(Info_Log{
			LOG_ERROR,
			"����ǰSE : " + cmd
		});
			throw (OJ_ERROR)OJ_SE;
		}

		//����������Ϣ����ʾ�������
		if (0 != get_file_size(path_ceinfo.c_str())){
			throw (OJ_ERROR)OJ_CE;
		}

	}catch(OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"����ʱ��������"
		});
		throw;
	}

	return 0;
}