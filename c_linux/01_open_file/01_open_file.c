/*
 ============================================================================
 Name        : 01_open_file.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		// 提供open()函数
#include <sys/types.h>	// 提供mode_t类型
#include <sys/stat.h>	// 提供open()函数的符号
#include <unistd.h>		// 提供close()函数

int main(void) {

	int f;									// 声明变量f，用于保存文件标识符
	const char *f_path = "test";			// 定义路径字符串
	mode_t f_attrib;						// 声明mode_t型变量，保存文件属性

	f_attrib = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
											// 为umask变量赋值

	f = open(f_path, O_RDONLY);				// 以只读方式打开文件
	if(f == -1){							// 判断文件是否打开成功
		f = open(f_path, O_RDWR | O_CREAT, f_attrib);	// 创建心文件
		if(f != -1){						// 判断文件是否创建成功
			puts("创建一个心文件");
		}
		else{
			puts("无法创建新文件，程序退出 ");
			return 1;
		}//
	}
	else{
		puts("文件打开成功 ");
	}
	close(f);								// 关闭文件

	return 0;
}
