/*
 ============================================================================
 Name        : 04_rmdir.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>


int main(void) {
	if(mkdir("testdir", 0774) != -1){	// 创建一个新目录
		puts("创建目录成功");
	}
	else{
		return 1;
	}
	if(creat("test1", 0664) != -1){		// 创建一个新文件
		puts("创建文件成功");
	}
	else{
		return 1;
	}

	if(unlink("test1") != -1){				// 删除刚才创建的文件
		puts("删除文件成功");
	}
	else{
		return 1;
	}
	if(rmdir("testdir") != -1)			// 删除刚才创建的目录
	{
		puts("删除目录成功");
	}
	else{
		return 1;
	}
	return EXIT_SUCCESS;
}
