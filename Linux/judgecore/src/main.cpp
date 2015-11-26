#include "../include/head.h"

int main(int argc, char const *argv[])
{
	OJ_Info info;	//评测信息
	OJ_Reinfo resinfo;	//评测结果信息
	queue<string> que_path;
	try{	
		Config::setpath(PH_CFG);	
		Config::load();			//加载配置文件

		init_param(argc,argv,info);	//初始化评测参数 

		resinfo.msg = OJ_AC;		//初始化评测结果
		resinfo.time = 0;		
		resinfo.memory = 0;		

		findInfiles(PH_IO+info.pro_id, que_path);	//寻找输入输出数据

		//切换目录到指定运行ID文件夹
		if(-1 == chdir((PH_RUN+info.run_id).c_str())){
			throw (OJ_ERROR) OJ_FILE_NONE;
		} 

		/*重判时清理数据*/
		 string 	cmd_del = "cp Main.cpp ../../code/"+info.run_id+".cpp";
		 system(cmd_del.c_str());
		 cmd_del = "-rm *";
		 system(cmd_del.c_str());
	 	 cmd_del = "cp ../../code/"+info.run_id+".cpp Main.cpp";
		 system(cmd_del.c_str());

		/*编译*/
		Compile cpj(info);
		cpj.run_cpp();

		
		/*按照不同的输入数据运行*/
		while(false == que_path.empty()){
			info.title_in = que_path.front();
			que_path.pop();

			Sandbox sbj(info);
			OJ_Reinfo resinfo_tmp = sbj.cpp();
			
			/*取最大值作为返回数据*/
			resinfo.time = max(resinfo.time, resinfo_tmp.time);
			resinfo.memory = max(resinfo.memory, resinfo_tmp.memory);
			
			Outjudge outJ(info);
			outJ.tons();
			outJ.nsjudge();
			outJ.judge();
		}

		throw (OJ_ERROR)OJ_AC;
	}catch(OJ_ERROR msg){
		string message_judge =  "";
		switch(msg)
		{
			case OJ_AC:
				resinfo.msg = msg;
				message_judge = "答案正确 AC";
				break;
			case OJ_WA:
				resinfo.msg = msg;
				message_judge = "答案错误 WA";
				break;
			case OJ_CE:
				resinfo.msg = msg;
				message_judge = "编译错误 CE";
				break;
			case OJ_PE:
				resinfo.msg = msg;
				message_judge = "格式错误 PE";
				break;
			case OJ_RE:
				resinfo.msg = msg;
				message_judge = "运行时出错 RE";
				break;
			case OJ_PF:
				resinfo.msg = msg;
				message_judge = "程序出现未允许的操作 PF";
				break;
			case OJ_MLE:
				resinfo.msg = msg;
				message_judge = "内存超出限制 MLE";
				break;
			case OJ_OLE:
				resinfo.msg = msg;
				message_judge = "输出超出限制 OLE";
				break;
			case OJ_TLE:
				resinfo.msg = msg;
				message_judge = "时间超出限制 TLE";
				break;

			case OJ_CONFIG_OPEN:
				resinfo.msg = OJ_SE;
				message_judge = "配置文件打开错误";
				break;
			case OJ_DATABASE_CON:
				resinfo.msg = OJ_SE;
				message_judge = "数据库连接出错";
			case OJ_DATABASE_QUERY:
				resinfo.msg = OJ_SE;
				message_judge = "数据库连接出错";
			case OJ_FILE_NONE:
				resinfo.msg = OJ_SE;
				message_judge = "输入输出文件错误";
			case OJ_FILE_DIR:
				resinfo.msg = OJ_SE;
				message_judge = "切换目录失败";		
			case OJ_SE:
				resinfo.msg = OJ_SE;
				message_judge = "评测机系统发生错误 SE";
				break;
			default:
				resinfo.msg = OJ_SE;
				message_judge = "评测机系统发生未知错误 SE";
				break;
		}

		message_judge = "run_id = "+info.run_id+"\nresult = "+message_judge;
		
		Log::log(Info_Log{
			LOG_ERROR,
			message_judge
		});
		
	}

	/*结果输出*/
	Database mysql(info);
	mysql.updateresult(resinfo);
	
	return 0;
}