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

int init_damon()
{
	pid_t pid, sid;

	// 创建子进程，然后父进程退出
	pid = fork();
	if(pid < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}else if(pid > 0){  // 父进程
		exit(EXIT_SUCCESS);
	}

	// 子进程

	// 创建新会话和新进程组
	if((sid = setsid()) < 0){
		perror("setsid");
		exit(EXIT_FAILURE);
	}

	// 改变当前的工作目录到原来目录
	if((chdir("/home/steve-liu/code/ayitoj/judgecontrol/")) < 0){
		perror("chdir");
		exit(EXIT_FAILURE);
	}

	// 改变目录文件的创建模式
	umask(0);

	// 关闭不必要的文件描述符
	 // close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	// close(STDERR_FILENO);

	return 0;
}
