/*
 ============================================================================
 Name        : 14_dup.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>					// �����������������
#include <stdlib.h>
#include <sys/types.h>				// ��ͷ�ļ��ṩϵͳ���õı�־
#include <sys/stat.h>				// ��ͷ�ļ��ṩ����״̬����ز���������
#include <fcntl.h>					// ��ͷ�ļ������ļ�I/O������ر�־
#include <unistd.h>					// ��׼������

int main(void) {
	int fd;
	if ((fd = open("output", O_CREAT | O_RDWR, 0644)) == -1) {	// �򿪻򴴽��ļ�
		perror("�򿪻򴴽��ļ�����");
		return 1;
	}
	close(1);						// �رձ�׼���
	dup(fd);						// ����fd���ļ������� 1 ��
	close(fd);						// �ر��ļ������� fd
	puts("�������ݽ�������ļ���");
	return EXIT_SUCCESS;
}
