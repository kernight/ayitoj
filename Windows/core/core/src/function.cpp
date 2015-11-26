#include "../include/function.h"

//����ID
string RUN_ID = "";

long get_file_size(const char * filename)
{
	FILE *fp = NULL;

	fopen_s(&fp, filename, "r");

	if (NULL == fp){
		return 0;
	}

	fseek(fp, 0, SEEK_END);

	int len = ftell(fp);

	fclose(fp);

	return len;
}

int init_param(int argc,char const *argv[],OJ_Info &info)
{
	if(argc < 2){
		Log::log(Info_Log{
			LOG_ERROR,
			"�������������"
		});
		throw (OJ_ERROR)OJ_SE;
	}

	info.run_id = argv[0];
	info.pro_id = argv[1];

	RUN_ID = info.run_id;

	Database mysql(info);
	mysql.queryinfo(info);

	return 0;
}

/*����ָ��Ŀ¼�����������ļ�,���Ұ�·������ que_path*/
void findInfiles(string dir,queue<string>& que_path)
{
	try{
		//�ļ����    
		long   hFile = 0;
		//�ļ���Ϣ    
		struct _finddata_t fileinfo;

		string p;
		dir += "\\*.in";

		if ((hFile = _findfirst(dir.c_str(), &fileinfo)) != -1)  {
			do  {
				//�������Ŀ¼,�����б�  
				if (!(fileinfo.attrib   &   _A_SUBDIR)) {
					string title = fileinfo.name;
					int len = title.length();
					string name = title.substr(0, len-3);

					que_path.push(name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);

			_findclose(hFile);
		}
		if (que_path.empty()){
			throw (OJ_ERROR)OJ_FILE_NONE;
		}
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"�Ҳ�����������ļ�"
		});
		throw;
	}
}

//ִ�������У���ת����
int my_exec(string cmd, string path, int time_lim = 10)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE hout = CreateFile(path.c_str(),
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags |= STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdInput = NULL;
	si.hStdError = hout;
	si.hStdOutput = hout;

	bool res = CreateProcess(NULL, (LPSTR)cmd.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, time_lim*1000);

	CloseHandle(hout);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return res;
}

//�Ƚ������ļ��Ƿ���ͬ
bool file_cmp(string file1, string file2)
{
	char info[1024];
	sprintf(info, "%s �Ĵ�С = %d\n %s �Ĵ�С = %d", file1.c_str(), get_file_size(file1.c_str()),
							file2.c_str(), get_file_size(file2.c_str()));
	//��������ļ���һ����
	if (get_file_size(file1.c_str()) != get_file_size(file2.c_str())){
		Log::log(Info_Log{
		LOG_ERROR,
		"�ļ���һ���� \n" + string(info)
		});
		return false;
	}

	ifstream fin1(file1);
	ifstream fin2(file2);
	if (false == fin1.is_open()
		|| false == fin2.is_open()){
		Log::log(Info_Log{
			LOG_ERROR,
			"�ȶ��ļ���ʧ��"
		});
		throw (OJ_ERROR)OJ_SE;
	}

	char out = '\0';
	char an = '\0';
	while (fin1 >> out && fin2 >> an){
		if (out != an){
			return false;
		}
	}

	fin1.close();
	fin2.close();

	return true;
}