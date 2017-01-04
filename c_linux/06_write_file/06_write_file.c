/*
 ============================================================================
 Name        : 06_write_file.c
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

#define	LENGTH	2000
int main(void) {
	char c[LENGTH];					// 定义内存块
	int f, i;
	puts("输出要保存的文件信息：");
	if ((i = read(0, c, LENGTH)) < 1) {	// 从标准输入中读取数据，实际输入的长度赋值给i
		perror("读取失败");
		return 1;
	}
	f = open("outfile", O_RDWR | O_CREAT, 0664);	// 打开或新建一个文件
	if (f != -1) {
		if (write(f, c, i) != i) {				// 将内存块中长度为i的数据写入文件
			perror("写入失败");
		}
		puts("保存文件成功");
		close(f);
	}
	else {
		perror("打开文件");
	}


	return 0;
}
