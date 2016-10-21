#include "../include/compile.h"

Compile::Compile(OJ_Info info)
{
	m_info = info;
}

int Compile::run_cpp()
{
	try{
		string path_ceinfo = PH_RES;/*编译信息文件路径*/

		const char * CP_CPP[] = { "g++", "Main.cpp", "-o", "Main","-O2", "-Wall",
				"-lm", "--static", NULL
				  };
		if(0 == get_file_size("Main.cpp")){
			cerr<<"程序文件不存在"<<endl;
			throw OJ_SE;
		}
		
		int pid = fork();

		if(0 == pid){
			struct rlimit LIM;

			/*时间限制*/
			LIM.rlim_cur = LIM.rlim_max =  60;//单位 ms -> s
			setrlimit(RLIMIT_CPU, &LIM);

			/*栈限制*/
			LIM.rlim_cur = LIM.rlim_max = STD_MB*512;
			setrlimit(RLIMIT_STACK, &LIM);

			/*内存限制*/
			LIM.rlim_cur = LIM.rlim_max =  STD_MB *512;
			setrlimit(RLIMIT_AS, &LIM);

			freopen(path_ceinfo.c_str(), "w", stdout);
			freopen(path_ceinfo.c_str(), "w", stderr);

			execvp(CP_CPP[0], (char * const *)CP_CPP);

			exit(0);
		}else{
			int status = 0;
			waitpid(pid, &status,0);

			if(0 == get_file_size("Main")){ /*如果程序文件不存在，则返回编译出错*/
				throw (OJ_ERROR)OJ_CE;
			}
		}	
	}catch(OJ_ERROR msg){
		cerr<<"编译时发生错误"<<endl;
		throw;
	}

	return 0;
}