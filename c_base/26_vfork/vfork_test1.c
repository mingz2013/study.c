#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int child;
	int count = 1;
	printf("Before create son, the father's count is: %d\n", count);	// 创建进程之前
	child = vfork();	// 此时已经有两个进程在同时运行
	if(child < 0)
	{
		printf("error in vfork");
		exit(1);	// fork出错退出
	}
	if(child == 0)
	{
		printf("this is son, his pid is: %d and the count is : %d\n", getpid(), ++count);
	exit(1);

	}
	else
	{
		printf("after son, this is father, his pid is: %d and the count is: %d, and the child is %d\n", getpid(), count, child);
	}

	return 0;

}
