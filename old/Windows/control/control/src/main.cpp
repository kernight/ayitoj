#include "../include/head.h"

int main(int argc, char const *argv[])
{
	queue<OJ_Info> que_info;//待评测题目队列
	try{	
		Log::log(Info_Log{
			LOG_NORMAL,
			"加载配置文件"
		});
		Config::setpath(PH_CFG);
		Config::load();		//加载配置文件
		Log::log(Info_Log{
			LOG_NORMAL,
			"开始调度"
		});
		bool flag = false;
		while(true){
			Database Data;
			
			if (flag = !flag){
				cout << "\t";	
			}
			cout << "查找中......" << endl;
			
			
			Data.queryinfo(que_info);
			int key_pos = 5;	//每次最多评测5道题目

			while(false == que_info.empty() 
				&& 0 != key_pos ){

				OJ_Info info_new = que_info.front();
				que_info.pop();

				string cmd = PH_CORE;
				string cmd_param = info_new.run_id + " " + info_new.pro_id;
				STARTUPINFO si = { sizeof(si) };
				PROCESS_INFORMATION pi;
				si.dwFlags = STARTF_USESHOWWINDOW;        // 指定wShowWindow成员有效
				si.wShowWindow = SW_HIDE;                    // 此成员设为TRUE的话则显示新建进程的主窗口，FALSE不显示
		

				::CreateProcess(
					(LPCSTR)(cmd.c_str()),		// 评测核心的文件名
					(LPSTR)cmd_param.c_str(),	// 命令行参数
					NULL,                    // 默认进程安全性
					NULL,                    // 默认线程安全性
					FALSE,                   // 指定当前进程内的句柄不可以被子进程继承
					CREATE_NEW_CONSOLE,      // 为新进程创建一个新的控制台窗口，如果为NULL，不会创建新的窗口
					NULL,                    // 使用本进程的环境变量
					NULL,                    // 使用本进程的驱动器和目录
					&si,
					&pi);

				CloseHandle(pi.hProcess);		   
				CloseHandle(pi.hThread);

				key_pos --;
			}

			Sleep(2000);	//休眠两秒
		}
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"系统发生错误,测试"
		});
	}
	
	return 0;
}

