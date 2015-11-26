#include "../include/function.h"

int get_proc_status(int pid, const char * mark)
{
	FILE * pf;
	char fn[BUFFER_SIZE], buf[BUFFER_SIZE];
	int ret = 0;
	sprintf(fn, "/proc/%d/status", pid);
	pf = fopen(fn, "r");
	int m = strlen(mark);
	while (pf && fgets(buf, BUFFER_SIZE - 1, pf)){
		buf[strlen(buf) - 1] = 0;
		// cout<<"buf = "<<buf<<endl;
		if (strncmp(buf, mark, m) == 0){
			sscanf(buf + m + 1, "%d", &ret);
		}
	}
	if (pf){
		fclose(pf);
	}

	return ret;
}

long get_file_size(const char * filename)
{
	struct stat f_stat;

	if (stat(filename, &f_stat) == -1){
		return 0;
	}

	return (long) f_stat.st_size;
}

int init_param(int argc,char const *argv[],OJ_Info &info)
{
	if(argc < 3){
			Log::log(Info_Log{
			LOG_NORMAL,
			"评测机参数错误"
		});
		throw (OJ_ERROR)OJ_SE;
	}

	info.run_id = argv[1];
	info.pro_id = argv[2];

	Database mysql(info);
	mysql.queryinfo(info);

	return 0;
}

/*搜索指定目录下所有输入文件,并且把路径存入 que_path*/
void findInfiles(string dir,queue<string>& que_path)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	try{
		if((dp = opendir(dir.c_str())) == NULL) {
			throw (OJ_ERROR) OJ_FILE_DIR;
		}

		while((entry = readdir(dp)) != NULL) {
			lstat(entry->d_name,&statbuf);
			if(S_ISDIR(statbuf.st_mode)) {
				if(strcmp(".",entry->d_name) == 0 ||
					strcmp("..",entry->d_name) == 0){
						continue;
				}
			}
			/*将文件名进行记录*/
			string path_tmp = entry->d_name;
			int len = path_tmp.length();
			if('n' == path_tmp[len-1] && 'i' == path_tmp[len-2]){
				path_tmp = path_tmp.substr(0, len-3);
				que_path.push(path_tmp);
			}
		}
		if(que_path.empty()){
			throw (OJ_ERROR)OJ_FILE_NONE;
		}
	}catch(OJ_ERROR msg){
		closedir(dp);
		throw;
	}
	closedir(dp);
}