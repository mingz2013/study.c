#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
int main()
{
	extern int errno;
	char *path = "./tmpll";
	if(mkdir(path, 0766) == 0)// 创建目录
	{
		/*需要注意这里的权限设置参数，第一个0表示八进制数，766的含义如本章14.1节所述。如果目录创建成功，则返回0，返回值与0进行比较*/
		printf("created the directory %s.\n", path);	// 输出目录创建成功
	}else{
		printf("can't creat the directory %s.\n", path);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}

	if(rmdir(path) == 0)
	{
		printf("deleted the directory %s.\n", path);
	}else{
		printf("can't delete the directory %s.\n", path);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}

	return 0;
}
