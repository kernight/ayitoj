#include "../include/head.h"

int main(int argc, char const *argv[])
{
	OJ_Info info;
	OJ_Reinfo resinfo;
	queue<string> que_path;
	try{
		Config::setpath(PH_CFG);
		Config::load();			//���������ļ�

		init_param(argc, argv, info);	//��ʼ��������� 

		resinfo.msg = OJ_AC;		//��ʼ��������
		resinfo.time = 0;
		resinfo.memory = 0;

		findInfiles(PH_IO + info.pro_id, que_path);	//Ѱ�������������

		//����ʱ��������
		string path_run = PH_RUN + RUN_ID + "\\";
		string 	cmd_del = "copy " + path_run + "Main.cpp "+PH_CODE+ info.run_id + ".cpp";
		system(cmd_del.c_str());
		cmd_del = "del "+path_run+"*.* /q";
		system(cmd_del.c_str());
		cmd_del = "copy " + PH_CODE + info.run_id + ".cpp " + path_run + "Main.cpp ";
		system(cmd_del.c_str());
	
		//����
		Compile cpj(info);
		cpj.run_cpp();
		
		//���ղ�ͬ��������������
		while (false == que_path.empty()){
			info.title_in = que_path.front();
			que_path.pop();

			Sandbox sbj(info);
			OJ_Reinfo resinfo_tmp = sbj.cpp();

			//ȡ���ֵ��Ϊ��������
			resinfo.time = max(resinfo.time, resinfo_tmp.time);
			resinfo.memory = max(resinfo.memory, resinfo_tmp.memory);
		
			Outjudge outJ(info);
			outJ.tons();
			outJ.nsjudge();
			outJ.judge();

		}
		
		throw (OJ_ERROR)OJ_AC;
	}
	catch (OJ_ERROR msg){
		string message_judge = "";
		switch (msg)
		{
		case OJ_AC:
			resinfo.msg = msg;
			message_judge = "����ȷ AC";
			break;
		case OJ_WA:
			resinfo.msg = msg;
			message_judge = "�𰸴��� WA";
			break;
		case OJ_CE:
			resinfo.msg = msg;
			message_judge = "������� CE";
			break;
		case OJ_PE:
			resinfo.msg = msg;
			message_judge = "��ʽ���� PE";
			break;
		case OJ_RE:
			resinfo.msg = msg;
			message_judge = "����ʱ���� RE";
			break;
		case OJ_PF:
			resinfo.msg = msg;
			message_judge = "�������δ����Ĳ��� PF";
			break;
		case OJ_MLE:
			resinfo.msg = msg;
			message_judge = "�ڴ泬������ MLE";
			break;
		case OJ_OLE:
			resinfo.msg = msg;
			message_judge = "����������� OLE";
			break;
		case OJ_TLE:
			resinfo.msg = msg;
			message_judge = "ʱ�䳬������ TLE";
			break;

		case OJ_CONFIG_OPEN:
			resinfo.msg = OJ_SE;
			message_judge = "�����ļ��򿪴���";
			break;
		case OJ_DATABASE_CON:
			resinfo.msg = OJ_SE;
			message_judge = "���ݿ����ӳ���";
		case OJ_DATABASE_QUERY:
			resinfo.msg = OJ_SE;
			message_judge = "���ݿ����ӳ���";
		case OJ_FILE_NONE:
			resinfo.msg = OJ_SE;
			message_judge = "��������ļ�����";
		case OJ_FILE_DIR:
			resinfo.msg = OJ_SE;
			message_judge = "�л�Ŀ¼ʧ��";
		case OJ_SE:
			resinfo.msg = OJ_SE;
			message_judge = "�����ϵͳ�������� SE";
			break;
		default:
			resinfo.msg = OJ_SE;
			message_judge = "�����ϵͳ����δ֪���� SE";
			break;
		}

		Log::log(Info_Log{
			LOG_ERROR,
			message_judge
		});

	}catch (...){
		resinfo.msg = OJ_SE;
		Log::log(Info_Log{
			LOG_ERROR,
			"�����ϵͳ����δ֪���� SE"
		});
	}

	//������浽���ݿ�
	Database mysql(info);
	mysql.updateresult(resinfo);

	return 0;

}
