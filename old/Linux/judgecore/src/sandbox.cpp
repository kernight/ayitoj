#include "../include/sandbox.h"

Sandbox::Sandbox(OJ_Info info)
{
	m_info = info;
}

OJ_Reinfo Sandbox::cpp()
{
	OJ_Reinfo res;

	try{
		pid_t pid = fork();

		if(-1 == pid){
			throw (OJ_ERROR) OJ_SE;
		}else if(0 == pid){
			run_cpp();
		}else{
			res = watch_cpp(pid);
		}
	}catch(OJ_ERROR msg){
		throw ;
	}

	return res;
}

int Sandbox::run_cpp()
{
	try{
		nice(19);//修改优先级

		string infile   = "../../" + PH_IO +  m_info.pro_id + "/" + m_info.title_in + ".in";
		string outfile = m_info.pro_id + "-" + m_info.title_in + ".out";

		if(-1 == ptrace(PTRACE_TRACEME, 0, NULL, NULL)){
			cerr<<"跟踪失败"<<endl;
			throw ;
		}

		struct rlimit LIM; //资源限制项
		/*时间限制*/
		LIM.rlim_cur = LIM.rlim_max =  m_info.time_lim/1000;//单位 ms -> s
		setrlimit(RLIMIT_CPU, &LIM);

		alarm(0);
		alarm(m_info.time_lim/1000);

		/*文件限制*/
		LIM.rlim_cur = STD_F_LIM;
		LIM.rlim_max = STD_F_LIM + STD_MB;
		setrlimit(RLIMIT_FSIZE, &LIM);

		/*进程限制*/
		LIM.rlim_cur = LIM.rlim_max = 1;
		setrlimit(RLIMIT_NPROC, &LIM);

		/*栈限制*/
		LIM.rlim_cur = LIM.rlim_max = STD_MB;
		setrlimit(RLIMIT_STACK, &LIM);

		/*内存限制*/
		LIM.rlim_cur = LIM.rlim_max =  STD_KB *m_info.mem_lim*2;
		setrlimit(RLIMIT_AS, &LIM);

		/*运行测试程序*/
		freopen(infile.c_str(), "r", stdin);
		freopen(outfile.c_str(), "w", stdout);
		//freopen("error.info", "w", stderr);

		execl("./Main", "./Main", (char *)NULL);
	
		exit(0);
	}catch(...){
		cerr<<"子进程运行时出错"<<endl;
		exit(0);
	}
	
	return 0;
}



OJ_Reinfo Sandbox::watch_cpp(pid_t pid)
{
	OJ_Reinfo res;

	try{
		string outfile  = m_info.pro_id + "-" + m_info.title_in + ".out";
		string ansfile = "../../" + PH_IO + m_info.pro_id + "/" + m_info.title_in + ".out";

		int topmemory = 0;
		int tempmemory = 0;
		int status = 0 ;
		int sig = 0;
		int  exitcode = 0;
		struct user_regs_struct reg;
		struct rusage ruse;

		if(topmemory==0) {
			topmemory= get_proc_status(pid, "VmRSS:") << 10;
		}
		while (1){
			wait4(pid, &status, WUNTRACED, &ruse);

			tempmemory = get_proc_status(pid, "VmPeak:") << 10;

			if (tempmemory > topmemory){
				topmemory = tempmemory;
			}

			if (topmemory > m_info.mem_lim * STD_KB){
					throw (OJ_ERROR) OJ_MLE;
				ptrace(PTRACE_KILL, pid, NULL, NULL);
			}
			
			if (0 != WIFEXITED(status)){	//子进程正常退出
				break;
			}

			if (get_file_size(outfile.c_str()) > get_file_size(ansfile.c_str()) * 2){
				throw (OJ_ERROR) OJ_OLE;
				ptrace(PTRACE_KILL, pid, NULL, NULL);
				break;
			}			

			exitcode = WEXITSTATUS(status);

			if (exitcode != 0x05 && exitcode != 0){/*exitcode == 5 waiting for next CPU allocation  */
				switch (exitcode)
				{
					case SIGCHLD:
						alarm(0);
					case SIGALRM:
					case SIGKILL:
					case SIGXCPU:
						throw (OJ_ERROR) OJ_TLE;
						break;
					case SIGXFSZ:
						throw (OJ_ERROR) OJ_OLE;
						break;
					default:
						throw (OJ_ERROR) OJ_RE;
						break;
				}
			}

			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);

				switch (sig)
				{
					case SIGCHLD:
						alarm(0);
					case SIGALRM:
					case SIGKILL:
					case SIGXCPU:
						throw (OJ_ERROR) OJ_TLE;
						break;
					case SIGXFSZ:
						throw (OJ_ERROR) OJ_OLE;
						break;
					default:
						throw (OJ_ERROR) OJ_RE;
						break;
				}
			}

			/*检查系统调用*/
			ptrace(PTRACE_GETREGS, pid, NULL, &reg);
			
			// if (call_counter[reg.REG_SYSCALL] ){
			// 	//call_counter[reg.REG_SYSCALL]--;
			// }else if (0) {
			// 	call_counter[reg.REG_SYSCALL] = 1;
			// }else { //do not limit JVM syscall for using different JVM
			// 	throw (OJ_ERROR) OJ_PF;
			// 	ptrace(PTRACE_KILL, pidApp, NULL, NULL);
			// }
			// int usedtime = 0;
			// printf("%lld\n%lld\n%lld\n%lld\n",ruse.ru_utime.tv_sec,ruse.ru_utime.tv_usec,ruse.ru_stime.tv_sec,ruse.ru_stime.tv_usec);
			// usedtime += (ruse.ru_stime.tv_sec * 1000 + ruse.ru_stime??
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
			
		ptrace(PTRACE_KILL, pid, NULL, NULL);

		res.time = 0;
		res.memory = topmemory/1024;
		// cout<<res.memory<<endl;
	}catch(OJ_ERROR msg){
		ptrace(PTRACE_KILL, pid, NULL, NULL);
		cerr<<"运行程序时出错"<<endl;
		throw ;
	}

	return res;
}