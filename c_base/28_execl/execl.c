#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	printf("Executing ls\n");
	execl("/bin/ls", "ls", "-l", NULL);

	// 如果execl返回，说明调用失败
	perror("execl failed to run ls");
	
	return 0;
}
