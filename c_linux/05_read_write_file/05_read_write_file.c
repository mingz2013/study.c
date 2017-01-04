/*
 ============================================================================
 Name        : 05_read_write_file.c
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

#define	LENGTH 2000					// 内存块最大长度
int main(void) {
	char c[LENGTH];					// 定义内存块
	int f, i, j = 0;
	f = open("/usr/include/gnu-versions.h", // 打开指定路径文件
			O_RDONLY,						// 打开方式为只读
			LENGTH							// 每次读入到缓冲区的字节为2000
			);
	if(f != -1){							// 判断文件是否打开成功
		i = read(f, c, LENGTH);				// 从文件读取指定长度的数据，将实际长度赋值给i
		if(i > 0){							// 判断是否正确读取
			for( ; i > 0; i--)				// 以实际长度作为循环次数
			{
				putchar(c[j++]);			// 输出指定位置的字符
			}
		}
		else{
			perror("读取");					// 输出错误信息
		}

	}
	else{
		perror("打开文件");
	}

	return 0;
}
