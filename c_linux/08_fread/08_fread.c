/*
 ============================================================================
 Name        : 08_fread.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define	SIZE	65536			// 用于定义缓冲区大小，64KB
#define	LENGTH	1024			// 用于定义每次读取的长度，1KB
int main(void) {
	char buf[SIZE] = {0};		// 定义缓冲区
	FILE *fp;					// 定义文件流指针
	fp = fopen("/usr/include/gnu-versions.h", "r");	// 打开文件
	if(fp != NULL){
		if (fread(buf, LENGTH, SIZE / LENGTH, fp) >= 0) {	// 读取数据到缓冲区
			puts("读取文件成功");
		} else {
			perror("读取文件失败");
			return 1;
		}
	}
	else
	{
		perror("打开文件");
	}
	fclose(fp);					// 关闭被读取的文件
	fp = fopen("copy", "rw+");	// 以读写模式打开文件，该文件必须是以存在的
	if(fp != NULL) {
		if (fwrite(buf, LENGTH, SIZE / LENGTH, fp) >= 0) {	// 将缓冲区内的数据写入文件
			fflush(fp); 		// 立即将缓冲区待写入的数据写入文件
			puts("写入文件成功");
		} else {
			perror("写入文件失败");
			return 1;
		}
	}
	else {
		perror("打开文件");
	}
	if (fclose(fp) != -1) {
		puts("关闭文件成功");
	} else {
		perror("关闭文件");
	}
	return EXIT_SUCCESS;
}
