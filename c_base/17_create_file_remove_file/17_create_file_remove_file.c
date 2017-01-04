#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
int main()
{
	extern int errno;
	char *path = "./tmp.txt";
	if(creat(path, 0766) == -1)
	{
		printf("can't create the file %s.\n", path);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}else{
		printf("created file %s.\n", path);
	}

	if(remove(path) == 0)
	{
		printf("Deleted file %s.\n", path);
	}else{
		printf("can't delete the file %s.\n", path);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}

	return 0;
}
