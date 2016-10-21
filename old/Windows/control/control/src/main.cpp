#include "../include/head.h"

int main(int argc, char const *argv[])
{
	queue<OJ_Info> que_info;//��������Ŀ����
	try{	
		Log::log(Info_Log{
			LOG_NORMAL,
			"���������ļ�"
		});
		Config::setpath(PH_CFG);
		Config::load();		//���������ļ�
		Log::log(Info_Log{
			LOG_NORMAL,
			"��ʼ����"
		});
		bool flag = false;
		while(true){
			Database Data;
			
			if (flag = !flag){
				cout << "\t";	
			}
			cout << "������......" << endl;
			
			
			Data.queryinfo(que_info);
			int key_pos = 5;	//ÿ���������5����Ŀ

			while(false == que_info.empty() 
				&& 0 != key_pos ){

				OJ_Info info_new = que_info.front();
				que_info.pop();

				string cmd = PH_CORE;
				string cmd_param = info_new.run_id + " " + info_new.pro_id;
				STARTUPINFO si = { sizeof(si) };
				PROCESS_INFORMATION pi;
				si.dwFlags = STARTF_USESHOWWINDOW;        // ָ��wShowWindow��Ա��Ч
				si.wShowWindow = SW_HIDE;                    // �˳�Ա��ΪTRUE�Ļ�����ʾ�½����̵������ڣ�FALSE����ʾ
		

				::CreateProcess(
					(LPCSTR)(cmd.c_str()),		// ������ĵ��ļ���
					(LPSTR)cmd_param.c_str(),	// �����в���
					NULL,                    // Ĭ�Ͻ��̰�ȫ��
					NULL,                    // Ĭ���̰߳�ȫ��
					FALSE,                   // ָ����ǰ�����ڵľ�������Ա��ӽ��̼̳�
					CREATE_NEW_CONSOLE,      // Ϊ�½��̴���һ���µĿ���̨���ڣ����ΪNULL�����ᴴ���µĴ���
					NULL,                    // ʹ�ñ����̵Ļ�������
					NULL,                    // ʹ�ñ����̵���������Ŀ¼
					&si,
					&pi);

				CloseHandle(pi.hProcess);		   
				CloseHandle(pi.hThread);

				key_pos --;
			}

			Sleep(2000);	//��������
		}
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"ϵͳ��������,����"
		});
	}
	
	return 0;
}

