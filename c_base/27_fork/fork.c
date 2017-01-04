#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	printf("Now only one process\n");
	printf("Calling fork...\n");
	pid = fork();
	if(pid < 0)
	{
		printf("Fork fail\n");
	}
	else if(pid == 0)
	{
		printf("I'm the child\n");
	}
	else
	{
		printf("I'm the parent, child has pid %d\n", pid);
	}
	return 0;
}