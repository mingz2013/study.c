/*
 ============================================================================
 Name        : 07_file.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp;				// 定义文件流指针
	fp = fopen("/usr/include/gnu-versions.h", "r");
								// 以只读方式打开文件，函数返回的文件流指针赋给*fp
	if (fp != NULL) {
		puts("打开文件成功");
	} else {
		perror("打开文件");
		return 1;
	}
	if (fclose(fp) != -1) {
		puts("关闭文件成功");
	} else {
		perror("关闭文件");
		return 1;
	}
	return EXIT_SUCCESS;
}
