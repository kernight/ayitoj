#include "../include/compile.h"

Compile::Compile(OJ_Info info)
{
	m_info = info;
}

int Compile::run_cpp()
{
	try{
		string path_run = PH_RUN + RUN_ID + "\\";
		string path_ceinfo = path_run + PH_RES;/*编译信息文件路径*/
		
		if (0 == get_file_size((path_run + "Main.cpp").c_str())){
			Log::log(Info_Log{
				LOG_ERROR,
				"程序文件不存在"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		//设置临时环境变量,将编译器目录放进去
		char curr_path[1024];//当前工作目录
		GetCurrentDirectory(1024, curr_path);

		char *path = getenv("Path");//环境变量
		if (NULL == path){
			Log::log(Info_Log{
				LOG_ERROR,
				"环境变量读取错误"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		string PathShell = "Path=" + (string)path + ';' + curr_path +"\\"+ Config::read("COMPILE_PATH");
		Log::log(Info_Log{
			LOG_NORMAL,
			"环境变量" + PathShell
		});
		if (0 != putenv(PathShell.c_str())){
			Log::log(Info_Log{
				LOG_ERROR,
				"环境变量设置错误"
			});
			throw (OJ_ERROR)OJ_SE;
		}
		
		string cmd = "g++ "+ path_run + "Main.cpp -o " + path_run + "Main -O2 -w -lm --static";

		if (false == my_exec(cmd, path_ceinfo, 10)){
			Log::log(Info_Log{
			LOG_ERROR,
			"编译前SE : " + cmd
		});
			throw (OJ_ERROR)OJ_SE;
		}

		//如果有输出信息，表示编译出错
		if (0 != get_file_size(path_ceinfo.c_str())){
			throw (OJ_ERROR)OJ_CE;
		}

	}catch(OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"编译时发生错误"
		});
		throw;
	}

	return 0;
}