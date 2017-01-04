#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("The current process ID is %d\n", getpid());
	return 0;
}
