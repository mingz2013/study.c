/*
 ============================================================================
 Name        : 11_fork.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>						// 标准输入输出函数库
#include <stdlib.h>						// 常用工具函数库

#include <sys/types.h>					// 该头文件提供系统调用的标志
#include <sys/stat.h>					// 该头文件提供系统状态信息和相关函数
#include <sys/uio.h>					// 该头文件提供进程I/O操作的相关函数
#include <unistd.h>						// 函数标准库
#include <fcntl.h>						// 文件操作相关函数库
#include <string.h>						// 字符串操作函数库
#include <sys/wait.h>					// wait调用相关函数库


int main(void) {

	char buf[100] = {0};				// 定义缓冲区
	pid_t cld_pid;						// 定义该结构保存子进程的PID
	int fd;
	int status;							// 用于wait调用时的参数
	if ((fd = open("temp", O_CREAT | O_RDWR | O_TRUNC, 0664)) == -1) { // 打开或新建文件
		perror("创建文件");
		exit(1);
	}
	strcpy(buf, "父进程数据");
	if ((cld_pid = fork()) == 0) {		// 创建子进程，并判断自己是否是子进程
		strcpy(buf, "子进程数据");
		puts("子进程正在工作:");
		printf("子进程-子进程PID是%d\n", getpid());	// 输出子进程的PID
		printf("子进程-父进程PID是%d\n", getppid());	// 输出父进程的PID
		write(fd, buf, strlen(buf));
		close(fd);
		exit(0);
	} else {
		puts("父进程正在工作：");
		printf("父进程-父进程PID是%d\n", getpid());	// 输出父进程的PID
		printf("父进程-子进程PID是%d\n", cld_pid);	// 输出子进程的PID
		write(fd, buf, strlen(buf));
		close(fd);
	}
	wait(&status);							// 等待子进程结束
	return 0;
}
