#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int count = 0;
	pid_t pid;	// 此时仅有一个进程

	pid = fork();	// 此时已经有两个进程在同时运行
	if(pid < 0)
	{
		printf("error in fork!");
		exit(1);	// fork 出错退出
	}
	else if(pid == 0)
	{
		printf("I am the child process, the count is %d, my process ID is %d\n", count, getpid());
	}
	else
	{
		printf("I am the parent process, the count is %d, my process ID is %d\n", ++count, getpid());
	}
	return 0;
}
