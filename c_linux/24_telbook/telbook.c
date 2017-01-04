#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

struct telnum
{
	char name[7];	// 姓名
	char tel[13];	// 电话号码
};	// 定义保存一个电话号码的结构体

struct telnum num[100]; // 全局变量，一个结构体数组
int i;	// 全局变量，当前记录的条数

int menu() // 菜单函数，完成菜单的显示和选择
{
	int i;
	i = 0;
	while(1)
	{
		printf("Please select a menu:\n");
		printf("	1: add a number.\n");
		printf("	2: all the number.\n");
		printf("	3: select a number by name.\n");
		printf("	4: delete a number.\n");
		printf("	5: save to file.\n");
		printf("	6: load numbers from file.\n");
		printf("	0: exit.\n");

		scanf("%d", &i);	// 输入信息
		if(i == 0)
		{
			printf("Byebye\n");
			exit(1);
		}
		if(i < 1 || i > 6)	// 不再正确的范围内，则显示错误
		{
			printf("error.\n");
			continue;
		}
		else
		{
			return i;
		}

	}
}

void shownum(struct telnum t) // 显示电话函数，其参数是一个结构体，显示结构体信息
{
	printf("name	: %s\n", t.name);	// 显示姓名
	printf("tel 	: %s\n", t.tel);		// 显示电话
}

struct telnum addnum()	// 添加电话函数，完成电话号码的添加，返回一个结构体
{
	struct telnum numtmp;	// 定义一个电话号码结构体变量
	char na[7], tel[13];	
	printf("add a telephone number:\n");
	printf("please input the name:\n");
	scanf("%s", na);	// 输入姓名
	printf("please input the num:\n");
	scanf("%s", tel);
	strcpy(numtmp.name, na);	// 将变量复制到结构体成员上
	strcpy(numtmp.tel, tel);
	return numtmp;
}

void selectbyname()	// 查找函数，输入姓名，查找到这个用户的电话
{
	char na[20];	
	int n, j;
	n = 0;
	printf("select a number by name:\n");
	printf("please input a name:\n");
	scanf("%s", na);
	for (j = 0; j < i; j++)
	{
		if(strcmp(num[j].name, na) == 0)
		{
			shownum(num[j]);
			n++;
		}
	}
	if(n == 0)
	{
		printf("no such a name\n");
	}
}

void delenum()	// 删除电话号码函数，输入姓名，删除这个用户的电话号码
{
	char na[20];
	int j, n;
	n = 0;
	printf("delete a num by name:\n");
	printf("please input a name:\n");
	scanf("%s", na);
	for(j = 0; j < i; j++)
	{
		if(strcmp(num[j].name, na) == 0)
		{
			n++;
			for(; j < i; j++)
			{
				num[j] = num[j + 1];	// 后面的变量向前移动
			}
			i--;	// 总数-1
			break;
		}
	}
	if(n == 0)
	{
		printf("no such a name\n");
	}
}

void savetofile()	// 保存信息功能，将所有的电话号码保存到文件上
{
	int j, fd;
	char file[] = "./tel.txt";
	extern int errno;	// 设置错误号
	fd = open(file, O_WRONLY | O_CREAT);	// 打开文件
	if(fd != -1)
	{
		printf("opened file %s\n", file);
	}
	else
	{
		printf("cant't open file %s\n", file);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}

	for(j = 0; j < i; j++)
	{
		printf("	%d 	%s\n", j, num[j].name);	// 显示姓名
		write(fd, num[j].name, 7);	// 保存姓名
		write(fd, num[j].tel, 13);	// 保存电话
	}
	printf("saved.\n");
	close(fd);
}

void loadfromfile()	// 导入电话号码，从文件中读取电话号码
{
	int fd, t;
	i = 0;
	char na[7];
	char tel[13];
	char file[] = "./tel.txt";
	extern int errno;

	fd = open(file, O_RDONLY | O_CREAT);
	if(fd != -1)
	{
		printf("opened file %s\n", file);
	}
	else
	{
		printf("can't open file %s\n", file);
		printf("errno: %d\n", errno);
		printf("ERR: %s\n", strerror(errno));
	}

	while( read(fd, na, 7) > 0)	// 读取文件
	{
		printf("	%d 	%s\n", i, na);	// 显示姓名
		strcpy(num[i].name, na);
		read(fd, tel, 13);
		strcpy(num[i].tel, tel);
		i++;
	}

	close(fd);
}

int main(void)
{
	int s, j;
	i = 0;
	printf("-----Telphone Notebook.--------\n");

	while(1)
	{
		s = menu();

		if(s == 1)
		{
			num[i] = addnum();
			i++;
        } else if (s == 2)
		{
			for(j = 0; j < i; j++)
			{
				shownum(num[j]);
			}
        } else if (s == 3)
		{
			selectbyname();
        } else if (s == 4)
		{
			delenum();
        } else if (s == 5)
		{
			savetofile();
        } else if (s == 6)
		{
			loadfromfile();
        } else {
            return 0;
        }
	}
	return 0;
}
