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
	char c[LENGTH];					// �����ڴ��
	int f, i;
	puts("���Ҫ������ļ���Ϣ��");
	if ((i = read(0, c, LENGTH)) < 1) {	// �ӱ�׼�����ж�ȡ���ݣ�ʵ������ĳ��ȸ�ֵ��i
		perror("��ȡʧ��");
		return 1;
	}
	f = open("outfile", O_RDWR | O_CREAT, 0664);	// �򿪻��½�һ���ļ�
	if (f != -1) {
		if (write(f, c, i) != i) {				// ���ڴ���г���Ϊi������д���ļ�
			perror("д��ʧ��");
		}
		puts("�����ļ��ɹ�");
		close(f);
	}
	else {
		perror("���ļ�");
	}


	return 0;
}
