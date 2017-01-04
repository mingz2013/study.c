/*
 ============================================================================
 Name        : 12_beexec.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// 这是第一个文件，被调用者，文件名为beexec.c
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
extern char **environ;					// 声明全局变量，用于保存环境变量信息
int main(int argc, char* argv[]) {
	int i;
	puts("输出执行参数：");
	for(i = 0; i <= argc; i++)			// 以程序运行时输入的参数总数作为循环上线
	{
		printf("参数%d是:%s\n", i, argv[i]);	// 将所有的执行参数输出
	}
	puts("输出环境变量:");
	for (i = 0; environ[i] != NULL; i++) {	// 以环境变量总数作为循环上限
		printf("%s\n", environ[i]);			// 将所有环境变量输出
	}
}
