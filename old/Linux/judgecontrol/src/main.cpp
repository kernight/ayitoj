#include "../include/head.h"

int main(int argc, char const *argv[])
{
	queue<OJ_Info> que_info;//待评测题目队列
	try{	
		Config::setpath(PH_CFG);	
		Config::load();		//加载配置文件

		init_damon();
		cout<<"开始进行评测任务调度"<<endl;
		while(true){
			Database mysql;

			cout<<"任务查询中……"<<endl;
			
			mysql.queryinfo(que_info);
			int key_pos = 5;	//每次最多评测5道题目

			while(false == que_info.empty() 
				&& 0 != key_pos ){
				OJ_Info info_new = que_info.front();
				que_info.pop();

				pid_t pid = fork();
				if(0 == pid){
					char *param[5];

					param[0] = new char[128];
					param[1] = new char[128];
					param[2] = NULL;
					strncpy(param[0], info_new.run_id.c_str(), 128);
					strncpy(param[1], info_new.pro_id.c_str(), 128);

					/*运行评测机*/
					// 改变当前的工作目录到评测机目录
					if((chdir(PH_CORE.c_str())) < 0){
						perror("chdir");
						exit(EXIT_FAILURE);
					}
					string path_core = "./judgecore";
					execl(path_core.c_str(),path_core.c_str(),param[0],param[1],param[2]);	
				}

				key_pos --;
			}
			sleep(2);	//休眠两秒
		}
	}catch(...){
		Log::log(Info_Log{
			LOG_ERROR,
			"发生错误"
		});
	}
	
	return 0;
}