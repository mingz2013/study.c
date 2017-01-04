/*
 ============================================================================
 Name        : 13_Pipe.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>				// 基本输入输出函数库
#include <stdlib.h>
#include <unistd.h>				// 标准函数库
#include <sys/types.h>			// 该头文件提供系统调用的标志
#include <sys/wait.h>			// wait系统调用相关函数库
#include <string.h>				// 字符串处理函数库

int main(void) {
	int fd[2], cld_pid, status;	// 创建文件标识符数组
	char buf[200], len;			// 创建缓冲区
	if (pipe(fd) == -1) {		// 创建管道
		perror("创建管道出错");
		exit(1);
	}
	if ((cld_pid = fork()) == 0) {	// 创建子进程，判断进程自身是否是子进程
		close(fd[1]);				// 关闭写端口
		len = read(fd[0], buf, sizeof(buf));	// 从读端口中读取管道内数据
		buf[len] = 0;				// 为缓冲区内的数据加入字符串结束符
		printf("子进程从管道中读取的数据是: %s ", buf);	// 输出管道中的数据
		exit(0);
	} else {
		close(fd[0]);				// 关闭读端口
		sprintf(buf, "父进程为 子进程(PID=%d)创建该数据", cld_pid);	// 在缓冲区创建字符串信息
		write(fd[1], buf, strlen(buf));	// 通过写端口向管道写入数据
		exit(0);					// 结束父进程
	}
	return EXIT_SUCCESS;
}
