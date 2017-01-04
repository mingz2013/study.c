/*
 ============================================================================
 Name        : 10_file.c
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

#define	CTIME	3					// 定义操作数
struct inputvalue					// 该结构体保存每次输出操作信息
{
	unsigned int length;			// 每次输出的字符串长度
	fpos_t pos;						// 每次输出在文件中的位置
};
int main(void) {
	if (creat("text", 0664) == -1) {		// 创建文件
		perror("创建文件失败");
		return 1;
	}
	struct inputvalue iv[CTIME];	// 创建记录操作行为的结构体数组
	int i;
	FILE *fp;
	fp = fopen("text", "rw+");		// 打开文件
	for ( i = 0; i < CTIME; i++) {
		fgetpos(fp, &(iv[i].pos));	// 保存指针当前位置
		iv[i].length = fprintf(fp, "第%d次输出的数据", i);	// 输出数据到文件并记录输出信息的长度
	}
	fflush(fp);		// 立即将缓冲区内的数据输出到文件
	printf("文件的总长度为%ld\n", ftell(fp));	// 当前指针的位置一定在文件尾，指针的偏移量即文件长度
	rewind(fp);						// 将指针重新指向文件头
	for (i = 0; i < CTIME; i++) {
		fsetpos(fp, &(iv[i].pos));	// 用数组中的数据定位指针
		char *buf = malloc(iv[i].length + 1);	// 以数组中的输出长度加1的值动态分配缓冲区大小
		*(buf + iv[i].length + 1) = '\0';	// 将缓冲区最后一位置为字符串终结符
		fread(buf, iv[i].length, 1, fp);	// 读取输出长度的数据到缓冲区
		puts(buf);							// 输出缓冲区内的数据
		free(buf);							// 释放缓冲区
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
