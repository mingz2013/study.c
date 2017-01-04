/*
 ============================================================================
 Name        : 09_fscanf.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct buddy				// 定义结构体,用于保存数据格式
{
	char name[50];
	unsigned int tel;
	char address[200];
};
int main(void) {
	struct buddy bd1;		// 声明结构体变量
	if (creat("buddy", 0664) == -1) {		// 使用系统调用函数创建新文件
		perror("创建文件失败");
		return 1;
	}
	FILE *fp;				// 创建文件流指针
	fp = fopen("buddy", "rw+");			// 打开文件
	fprintf(fp, "<name>%s <tel>%d <address>%s ",	// 将格式化后的数据输出到文件中
			"Tom", 1234567890, "China");
	fclose(fp);				// 关闭文件
	fp = fopen("buddy", "rw+");			// 再次打开文件
	fscanf(fp, "<name>%s <tel>%d <address>%s ", // 读取格式化数据，并保存到bd1中
			bd1.name, &bd1.tel, bd1.address);
	fclose(fp);
	printf("<name>%s <tel>%d <address>%s ",bd1.name, bd1.tel, bd1.address);

	return EXIT_SUCCESS;
}
