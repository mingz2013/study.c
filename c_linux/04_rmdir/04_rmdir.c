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
	if(mkdir("testdir", 0774) != -1){	// ����һ����Ŀ¼
		puts("����Ŀ¼�ɹ�");
	}
	else{
		return 1;
	}
	if(creat("test1", 0664) != -1){		// ����һ�����ļ�
		puts("�����ļ��ɹ�");
	}
	else{
		return 1;
	}

	if(unlink("test1") != -1){				// ɾ���ղŴ������ļ�
		puts("ɾ���ļ��ɹ�");
	}
	else{
		return 1;
	}
	if(rmdir("testdir") != -1)			// ɾ���ղŴ�����Ŀ¼
	{
		puts("ɾ��Ŀ¼�ɹ�");
	}
	else{
		return 1;
	}
	return EXIT_SUCCESS;
}
