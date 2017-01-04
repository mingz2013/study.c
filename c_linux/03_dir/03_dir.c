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
#include <fcntl.h>									// �ṩopen()����
#include <unistd.h>
#include <dirent.h>									// �ṩĿ¼����������
#include <string.h>
#include <sys/stat.h>								// �ṩ���Բ�������
#include <sys/types.h>								// �ṩmode_t����

void scan_dir(char *dir, int depth)					// ����Ŀ¼ɨ�躯��
{
	DIR *dp;										// ������Ŀ¼��ָ��
	struct dirent *entry;							// ����dirent�ṹָ�뱣�����Ŀ¼
	struct stat statbuf;							// ����statbuf�ṹ�����ļ�����
	if((dp = opendir(dir)) == NULL){				// ��Ŀ¼�������Ŀ¼��ָ�룬�жϲ����Ƿ�ɹ�
		puts("�޷��򿪸�Ŀ¼");
		return;
	}
	chdir(dir);										// �л�����ǰĿ¼��ȥ
	while((entry = readdir(dp)) != NULL){			// ��ȡ��һ��Ŀ¼��Ϣ�����δ������ѭ��
		lstat(entry->d_name, &statbuf);				// ��ȡ��һ����Ա����
		if(S_IFDIR & statbuf.st_mode){				// �ж���һ����Ա�Ƿ���Ŀ¼
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0){
				continue;		// �����õĳ�Ա�Ƿ��š�.����".."����������ѭ��
			}
			printf("%*s%s/\n", depth, "", entry->d_name);// ���Ŀ¼����
			scan_dir(entry->d_name, depth + 4);// �ݹ��������ɨ����һ��Ŀ¼������
		}
		else{
			printf("%*s%s\n", depth, "", entry->d_name);// ������Բ���Ŀ¼�ĳ�Ա
		}
	}
	chdir("..");								// �ص���һ��Ŀ¼
	closedir(dp);								// �ر���Ŀ¼��
}

int main(void) {
	puts("ɨ��/homeĿ¼��");
	scan_dir("/home", 0);							// ����Ŀ¼ɨ�躯��
	puts("ɨ�����");									// ɨ�����ʱ�����ʾ��Ϣ
	return EXIT_SUCCESS;
}
