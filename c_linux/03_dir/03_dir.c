/*
 ============================================================================
 Name        : 03_dir.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>									// 提供open()函数
#include <unistd.h>
#include <dirent.h>									// 提供目录流操作函数
#include <string.h>
#include <sys/stat.h>								// 提供属性操作函数
#include <sys/types.h>								// 提供mode_t类型

void scan_dir(char *dir, int depth)					// 定义目录扫描函数
{
	DIR *dp;										// 定义子目录流指针
	struct dirent *entry;							// 定义dirent结构指针保存后续目录
	struct stat statbuf;							// 定义statbuf结构保存文件属性
	if((dp = opendir(dir)) == NULL){				// 打开目录，获得子目录流指针，判断操作是否成功
		puts("无法打开该目录");
		return;
	}
	chdir(dir);										// 切换到当前目录中去
	while((entry = readdir(dp)) != NULL){			// 获取下一级目录信息，如果未结束则循环
		lstat(entry->d_name, &statbuf);				// 获取下一级成员属性
		if(S_IFDIR & statbuf.st_mode){				// 判断下一级成员是否是目录
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0){
				continue;		// 如果获得的成员是符号“.”和".."，跳过本次循环
			}
			printf("%*s%s/\n", depth, "", entry->d_name);// 输出目录名称
			scan_dir(entry->d_name, depth + 4);// 递归调用自身，扫描下一级目录的内容
		}
		else{
			printf("%*s%s\n", depth, "", entry->d_name);// 输出属性不是目录的成员
		}
	}
	chdir("..");								// 回到上一级目录
	closedir(dp);								// 关闭子目录流
}

int main(void) {
	puts("扫描/home目录：");
	scan_dir("/home", 0);							// 调用目录扫描函数
	puts("扫描结束");									// 扫描结束时输出提示信息
	return EXIT_SUCCESS;
}
