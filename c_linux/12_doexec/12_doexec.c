/*
 ============================================================================
 Name        : 12_doexec.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
// 这是第二个文件，调用者，文件名为doexec.c
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
extern char **environ;					// 声明全局变量，用于保存环境变量信息
int main(int argc, char* argv[]) {
	puts("此信息可能无法输出");
	execve("beexec", argv, environ);	// 用beexec程序替换进程执行映像
	puts("正常情况下此信息无法输出");
}
