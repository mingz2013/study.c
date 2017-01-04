#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int count = 1;
	int child;
	printf("Before create son, the father's count is %d\n", count);

	if(!(child = vfork()))
	{
		// 这里是子进程执行区
		int i;
		for(i = 0; i < 100; i++)
		{
			printf("this is son, this i is: %d\n", i);
			if(i == 70)
			{
				exit(1);
			}
		}
	}
	else
	{
		// 父进程执行区
		printf("after son, this is father, his pid is : %d and the count is : %d, and the child is : %d\n", getpid(), count , child);
	}
	return 0;
}
