#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(void)
{
	int pid;
	// fork子进程
	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			execl("/bin/ls", "ls", "-l", NULL);
			perror("execl failed");
			exit(1);
		default:
			wait(NULL);
			printf("ls completed\n");
			exit(0);
	}
}
