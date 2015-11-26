#include "../include/sandbox.h"

#define CMPKEY_JOBOBJECT 1
#define CMPKEYERMINATE 2

HANDLE hIOCP = NULL;
HANDLE hIn = NULL;
HANDLE hOut = NULL;


OJ_ERROR Run_res = OJ_AC;

Sandbox::Sandbox(OJ_Info info)
{
	m_info = info;
}


OJ_Reinfo Sandbox::cpp()
{
	OJ_Reinfo res;

	try{
		PROCESS_INFORMATION pi;

		pi = run_cpp();

		res = watch_cpp(pi);

		
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return res;
	}catch(OJ_ERROR){
		throw ;
	}

	return res;
}

//IO完成端口监听线程回调函数
unsigned int __stdcall JobNotify_M(void *lpParam)
{
	HANDLE hIOCP = (HANDLE)lpParam;

	try{
		while (TRUE)
		{
			DWORD dwBytesTransferred;
			ULONG_PTR CompKey;
			LPOVERLAPPED po;

			//从IO完成端口中获取一个消息
			GetQueuedCompletionStatus(hIOCP, &dwBytesTransferred, &CompKey, &po, INFINITE);

			//退出消息
			if (CompKey == CMPKEYERMINATE)
			{
				//MessageBox(NULL, "监听线程退出", "提示", MB_OK);
				break;
			}

			//来自作业对象hJob的消息
			if (CompKey == CMPKEY_JOBOBJECT)
			{
				switch (dwBytesTransferred){
				case JOB_OBJECT_MSG_END_OF_JOB_TIME:
				case JOB_OBJECT_MSG_END_OF_PROCESS_TIME:
					//MessageBox(NULL, "作业限制时间耗尽", "提示", MB_OK); //TLE
					Run_res = OJ_TLE;
					break;
				case JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT:
					//MessageBox(NULL, ("运行的进程超过限制"), ("提示"), MB_OK);//PF
					Run_res = OJ_PF;
					break;
				case JOB_OBJECT_MSG_NEW_PROCESS:
					//MessageBox(NULL, ("作业中产生新进程"), ("提示"), MB_OK);
					break;
				case JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO:
					//MessageBox(NULL, ("作业中没有进程"), ("提示"), MB_OK);
					break;
				case JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT:
				case JOB_OBJECT_MSG_JOB_MEMORY_LIMIT:
					//MessageBox(NULL, ("作业的进程内存超过限制"), ("提示"), MB_OK);//RE
					Run_res = OJ_MLE;
					break;

				case JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS:
					//MessageBox(NULL, ("程序非正常退出"), ("提示"), MB_OK);//RE
					Run_res = OJ_RE;
					break;

				case JOB_OBJECT_MSG_EXIT_PROCESS:
					//MessageBox(NULL, ("作业的进程结束"), ("提示"), MB_OK);
					break;
				}
			}
		}
	}
	catch (...){
		throw;
	}
	return 0;
}
PROCESS_INFORMATION Sandbox::run_cpp()
{
	PROCESS_INFORMATION pi;
	try{
		string path_run = PH_RUN + RUN_ID + "\\";
		string path_exe = path_run+"Main.exe";

		string infile   = PH_IO +  m_info.pro_id + "\\" + m_info.title_in + ".in";
		string outfile = path_run + m_info.title_in + ".out";

		HANDLE hJob = CreateJobObject(NULL, NULL);

		JOBOBJECT_EXTENDED_LIMIT_INFORMATION ex_lim;
		ZeroMemory(&ex_lim, sizeof(ex_lim));

		JOBOBJECT_BASIC_LIMIT_INFORMATION & basicInfo = ex_lim.BasicLimitInformation;
		basicInfo.LimitFlags =
			JOB_OBJECT_LIMIT_PRIORITY_CLASS | /*限制job优先级*/
			JOB_OBJECT_LIMIT_PROCESS_TIME | /*限制job时间*/
			JOB_OBJECT_LIMIT_JOB_TIME |
			JOB_OBJECT_LIMIT_PROCESS_MEMORY | /*限制job内存*/
			JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION | /*遇到异常，让进程直接死掉。*/
			JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE | /*进程跟随job一起关闭*/
			JOB_OBJECT_LIMIT_BREAKAWAY_OK |
			JOB_OBJECT_LIMIT_ACTIVE_PROCESS;

		basicInfo.ActiveProcessLimit = 1;
		basicInfo.PriorityClass = NORMAL_PRIORITY_CLASS;      //优先级为默认
		basicInfo.PerProcessUserTimeLimit.QuadPart = m_info.time_lim * 10000;
		basicInfo.PerJobUserTimeLimit.QuadPart = m_info.time_lim * 10000;
		ex_lim.ProcessMemoryLimit = 1024 * m_info.mem_lim;

		SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &ex_lim, sizeof(ex_lim));

		//创建一个IO完成端口
		hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

		//创建一个线程监听IO完成端口通知消息
		HANDLE hThreadIOCP = (HANDLE)_beginthreadex(NULL, 0, JobNotify_M, hIOCP, 0, NULL);

		//将IO完成端口与作业关联
		JOBOBJECT_ASSOCIATE_COMPLETION_PORT jobacp;
		jobacp.CompletionKey = (PVOID)CMPKEY_JOBOBJECT;  //任意一个全局唯一的值
		jobacp.CompletionPort = hIOCP;                   //IO完成端口句柄

		SetInformationJobObject(hJob, JobObjectAssociateCompletionPortInformation, &jobacp, sizeof(jobacp));

		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		hIn = CreateFile(infile.c_str(), FILE_READ_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ,
								&sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		hOut = CreateFile(outfile.c_str(),FILE_APPEND_DATA,FILE_SHARE_WRITE | FILE_SHARE_READ,
							&sa,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

		if (INVALID_HANDLE_VALUE == hIn ||
			INVALID_HANDLE_VALUE == hOut){
			Log::log(Info_Log{
				LOG_ERROR,
				"打开输入输出文件错误"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		PROCESS_INFORMATION pi;
		STARTUPINFO si;
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags |= STARTF_USESTDHANDLES;
		si.wShowWindow = SW_HIDE;
		si.hStdInput = hIn;
		si.hStdError = hOut;
		si.hStdOutput = hOut;
		DWORD createFlag = CREATE_SUSPENDED | CREATE_NO_WINDOW | CREATE_BREAKAWAY_FROM_JOB;

		CreateProcess(path_exe.c_str(), NULL,NULL, NULL, TRUE,createFlag,NULL, NULL,&si, &pi);

		AssignProcessToJobObject(hJob, pi.hProcess);

		ResumeThread(pi.hThread);

		return pi;
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"子进程运行时出错"
		});
		throw (OJ_ERROR)OJ_SE;
	}
}


OJ_Reinfo Sandbox::watch_cpp(PROCESS_INFORMATION pi)
{
	OJ_Reinfo res;
	ZeroMemory(&res, sizeof(res));

	try{
		WaitForSingleObject(pi.hProcess, INFINITE);
		//发送一条消息给IO完成端口，结束IO完成端口线程
		PostQueuedCompletionStatus(hIOCP, 0, CMPKEYERMINATE, NULL);

		FILETIME ftime, temp;
		::GetProcessTimes(pi.hProcess, &temp, &temp, &temp, &ftime);

		ULARGE_INTEGER time2;
		time2.LowPart = ftime.dwLowDateTime;
		time2.HighPart = ftime.dwHighDateTime;

		long long time_use = time2.QuadPart / 10000;

		PROCESS_MEMORY_COUNTERS info;
		::GetProcessMemoryInfo(pi.hProcess, &info, sizeof(info));
		long long mem_use = info.PeakPagefileUsage / 1024;

		DWORD exitcode;
		if (0 == GetExitCodeProcess(pi.hProcess, &exitcode)){
			Log::log(Info_Log{
				LOG_ERROR,
				"获取退出码错误"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		char tmp[1024];
		sprintf(tmp, "运行时间 ：%lld", time_use);
		Log::log(Info_Log{
			LOG_NORMAL,
			tmp
		});

		sprintf(tmp, "运行内存 ：%lld", mem_use);
		Log::log(Info_Log{
			LOG_NORMAL,
			tmp
		});

		//如果沙箱运行出错
		if (OJ_AC != Run_res){
			throw (OJ_ERROR)Run_res;
		}

		//判断运行最终数据，消除沙箱的不精确性
		if (time_use > m_info.time_lim){
			throw (OJ_ERROR)OJ_TLE;
		}
		if (exitcode != 0){
			throw (OJ_ERROR)OJ_RE;
		}

		if (mem_use > m_info.mem_lim){
			throw (OJ_ERROR)OJ_MLE;
		}

		CloseHandle(hOut);
		CloseHandle(hIn);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		res.memory = mem_use;
		res.time = time_use;
	}catch(OJ_ERROR){
		Log::log(Info_Log{
			LOG_ERROR,
			"运行程序时出错"
		});
		throw ;
	}

	return res;
}