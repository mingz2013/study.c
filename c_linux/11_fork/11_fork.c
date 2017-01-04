/*
 ============================================================================
 Name        : 11_fork.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>						// ��׼�������������
#include <stdlib.h>						// ���ù��ߺ�����

#include <sys/types.h>					// ��ͷ�ļ��ṩϵͳ���õı�־
#include <sys/stat.h>					// ��ͷ�ļ��ṩϵͳ״̬��Ϣ����غ���
#include <sys/uio.h>					// ��ͷ�ļ��ṩ����I/O��������غ���
#include <unistd.h>						// ������׼��
#include <fcntl.h>						// �ļ�������غ�����
#include <string.h>						// �ַ�������������
#include <sys/wait.h>					// wait������غ�����


int main(void) {

	char buf[100] = {0};				// ���建����
	pid_t cld_pid;						// ����ýṹ�����ӽ��̵�PID
	int fd;
	int status;							// ����wait����ʱ�Ĳ���
	if ((fd = open("temp", O_CREAT | O_RDWR | O_TRUNC, 0664)) == -1) { // �򿪻��½��ļ�
		perror("�����ļ�");
		exit(1);
	}
	strcpy(buf, "����������");
	if ((cld_pid = fork()) == 0) {		// �����ӽ��̣����ж��Լ��Ƿ����ӽ���
		strcpy(buf, "�ӽ�������");
		puts("�ӽ������ڹ���:");
		printf("�ӽ���-�ӽ���PID��%d\n", getpid());	// ����ӽ��̵�PID
		printf("�ӽ���-������PID��%d\n", getppid());	// ��������̵�PID
		write(fd, buf, strlen(buf));
		close(fd);
		exit(0);
	} else {
		puts("���������ڹ�����");
		printf("������-������PID��%d\n", getpid());	// ��������̵�PID
		printf("������-�ӽ���PID��%d\n", cld_pid);	// ����ӽ��̵�PID
		write(fd, buf, strlen(buf));
		close(fd);
	}
	wait(&status);							// �ȴ��ӽ��̽���
	return 0;
}
