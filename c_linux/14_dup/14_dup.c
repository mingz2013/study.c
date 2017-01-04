/*
 ============================================================================
 Name        : 14_dup.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>					// 基本输入输出函数库
#include <stdlib.h>
#include <sys/types.h>				// 该头文件提供系统调用的标志
#include <sys/stat.h>				// 该头文件提供进程状态及相关操作函数库
#include <fcntl.h>					// 该头文件包含文件I/O操作相关标志
#include <unistd.h>					// 标准函数库

int main(void) {
	int fd;
	if ((fd = open("output", O_CREAT | O_RDWR, 0644)) == -1) {	// 打开或创建文件
		perror("打开或创建文件出错");
		return 1;
	}
	close(1);						// 关闭标准输出
	dup(fd);						// 复制fd到文件描述符 1 上
	close(fd);						// 关闭文件描述符 fd
	puts("该行数据将输出到文件中");
	return EXIT_SUCCESS;
}
