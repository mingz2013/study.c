/*
 ============================================================================
 Name        : 02_file.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		// �ṩopen()����
#include <sys/types.h>	// �ṩmode_t����
#include <sys/stat.h>	// �ṩopen()�����ķ���
#include <unistd.h>		// �ṩclose()����

int main(void) {

	int f;									// ��������f�����ڱ����ļ���ʶ��
	const char *f_path = "test";			// ����·���ַ���
	mode_t f_attrib;						// ����mode_t�ͱ����������ļ�����
	struct stat *buf = malloc(sizeof(stat));// ��̬����ṹ��*buf���ڴ�
											// struct stat ��stat.h�ṩ�ı����ļ����͵Ľṹ��
	f_attrib = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
											// Ϊumask������ֵ

	f = creat(f_path, f_attrib);			// ����һ�����ļ��������÷���Ȩ��
	if(f == -1){							// �ж��ļ��Ƿ�򿪳ɹ�
		puts("�ļ�����ʧ��");					// ���������Ϣ
		return 1;
	}
	else{
		puts("�ļ��򿪳ɹ� ");					// ����ɹ���Ϣ
	}
	fstat(f, buf);							// ͨ���ļ���ʶ����ȡ����Ȩ��
	if(buf->st_mode & S_IRUSR){				// ����buf�ڵ���Ϣ��ȡȨ��
		puts("������ӵ�ж�Ȩ��");
	}
	if(buf->st_mode & S_IRGRP){
		puts("Ⱥ��ӵ�ж�Ȩ��");
	}
	close(f);								// �ر��ļ�
	chmod(f_path, 0771);					// �޸ĸ��ļ���Ȩ��
	stat(f_path, buf);						// ͨ��·����ȡ����Ȩ��
	if(buf->st_mode & S_IWUSR){				// ����buf�ڵ���Ϣ��ȡȨ��
		puts("������ӵ��дȨ��");
	}
	if(buf->st_mode & S_IWGRP){
		puts("Ⱥ��ӵ��дȨ��");
	}
	free(buf);								// �ͷ�bufָ����ָ����ڴ�ռ�
	return 0;
}
