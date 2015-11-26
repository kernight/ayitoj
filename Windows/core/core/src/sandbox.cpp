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

//IO��ɶ˿ڼ����̻߳ص�����
unsigned int __stdcall JobNotify_M(void *lpParam)
{
	HANDLE hIOCP = (HANDLE)lpParam;

	try{
		while (TRUE)
		{
			DWORD dwBytesTransferred;
			ULONG_PTR CompKey;
			LPOVERLAPPED po;

			//��IO��ɶ˿��л�ȡһ����Ϣ
			GetQueuedCompletionStatus(hIOCP, &dwBytesTransferred, &CompKey, &po, INFINITE);

			//�˳���Ϣ
			if (CompKey == CMPKEYERMINATE)
			{
				//MessageBox(NULL, "�����߳��˳�", "��ʾ", MB_OK);
				break;
			}

			//������ҵ����hJob����Ϣ
			if (CompKey == CMPKEY_JOBOBJECT)
			{
				switch (dwBytesTransferred){
				case JOB_OBJECT_MSG_END_OF_JOB_TIME:
				case JOB_OBJECT_MSG_END_OF_PROCESS_TIME:
					//MessageBox(NULL, "��ҵ����ʱ��ľ�", "��ʾ", MB_OK); //TLE
					Run_res = OJ_TLE;
					break;
				case JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT:
					//MessageBox(NULL, ("���еĽ��̳�������"), ("��ʾ"), MB_OK);//PF
					Run_res = OJ_PF;
					break;
				case JOB_OBJECT_MSG_NEW_PROCESS:
					//MessageBox(NULL, ("��ҵ�в����½���"), ("��ʾ"), MB_OK);
					break;
				case JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO:
					//MessageBox(NULL, ("��ҵ��û�н���"), ("��ʾ"), MB_OK);
					break;
				case JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT:
				case JOB_OBJECT_MSG_JOB_MEMORY_LIMIT:
					//MessageBox(NULL, ("��ҵ�Ľ����ڴ泬������"), ("��ʾ"), MB_OK);//RE
					Run_res = OJ_MLE;
					break;

				case JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS:
					//MessageBox(NULL, ("����������˳�"), ("��ʾ"), MB_OK);//RE
					Run_res = OJ_RE;
					break;

				case JOB_OBJECT_MSG_EXIT_PROCESS:
					//MessageBox(NULL, ("��ҵ�Ľ��̽���"), ("��ʾ"), MB_OK);
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
			JOB_OBJECT_LIMIT_PRIORITY_CLASS | /*����job���ȼ�*/
			JOB_OBJECT_LIMIT_PROCESS_TIME | /*����jobʱ��*/
			JOB_OBJECT_LIMIT_JOB_TIME |
			JOB_OBJECT_LIMIT_PROCESS_MEMORY | /*����job�ڴ�*/
			JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION | /*�����쳣���ý���ֱ��������*/
			JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE | /*���̸���jobһ��ر�*/
			JOB_OBJECT_LIMIT_BREAKAWAY_OK |
			JOB_OBJECT_LIMIT_ACTIVE_PROCESS;

		basicInfo.ActiveProcessLimit = 1;
		basicInfo.PriorityClass = NORMAL_PRIORITY_CLASS;      //���ȼ�ΪĬ��
		basicInfo.PerProcessUserTimeLimit.QuadPart = m_info.time_lim * 10000;
		basicInfo.PerJobUserTimeLimit.QuadPart = m_info.time_lim * 10000;
		ex_lim.ProcessMemoryLimit = 1024 * m_info.mem_lim;

		SetInformationJobObject(hJob, JobObjectExtendedLimitInformation, &ex_lim, sizeof(ex_lim));

		//����һ��IO��ɶ˿�
		hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

		//����һ���̼߳���IO��ɶ˿�֪ͨ��Ϣ
		HANDLE hThreadIOCP = (HANDLE)_beginthreadex(NULL, 0, JobNotify_M, hIOCP, 0, NULL);

		//��IO��ɶ˿�����ҵ����
		JOBOBJECT_ASSOCIATE_COMPLETION_PORT jobacp;
		jobacp.CompletionKey = (PVOID)CMPKEY_JOBOBJECT;  //����һ��ȫ��Ψһ��ֵ
		jobacp.CompletionPort = hIOCP;                   //IO��ɶ˿ھ��

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
				"����������ļ�����"
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
			"�ӽ�������ʱ����"
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
		//����һ����Ϣ��IO��ɶ˿ڣ�����IO��ɶ˿��߳�
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
				"��ȡ�˳������"
			});
			throw (OJ_ERROR)OJ_SE;
		}

		char tmp[1024];
		sprintf(tmp, "����ʱ�� ��%lld", time_use);
		Log::log(Info_Log{
			LOG_NORMAL,
			tmp
		});

		sprintf(tmp, "�����ڴ� ��%lld", mem_use);
		Log::log(Info_Log{
			LOG_NORMAL,
			tmp
		});

		//���ɳ�����г���
		if (OJ_AC != Run_res){
			throw (OJ_ERROR)Run_res;
		}

		//�ж������������ݣ�����ɳ��Ĳ���ȷ��
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
			"���г���ʱ����"
		});
		throw ;
	}

	return res;
}