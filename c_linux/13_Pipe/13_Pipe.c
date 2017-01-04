/*
 ============================================================================
 Name        : 13_Pipe.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>				// �����������������
#include <stdlib.h>
#include <unistd.h>				// ��׼������
#include <sys/types.h>			// ��ͷ�ļ��ṩϵͳ���õı�־
#include <sys/wait.h>			// waitϵͳ������غ�����
#include <string.h>				// �ַ�����������

int main(void) {
	int fd[2], cld_pid, status;	// �����ļ���ʶ������
	char buf[200], len;			// ����������
	if (pipe(fd) == -1) {		// �����ܵ�
		perror("�����ܵ�����");
		exit(1);
	}
	if ((cld_pid = fork()) == 0) {	// �����ӽ��̣��жϽ��������Ƿ����ӽ���
		close(fd[1]);				// �ر�д�˿�
		len = read(fd[0], buf, sizeof(buf));	// �Ӷ��˿��ж�ȡ�ܵ�������
		buf[len] = 0;				// Ϊ�������ڵ����ݼ����ַ���������
		printf("�ӽ��̴ӹܵ��ж�ȡ��������: %s ", buf);	// ����ܵ��е�����
		exit(0);
	} else {
		close(fd[0]);				// �رն��˿�
		sprintf(buf, "������Ϊ �ӽ���(PID=%d)����������", cld_pid);	// �ڻ����������ַ�����Ϣ
		write(fd[1], buf, strlen(buf));	// ͨ��д�˿���ܵ�д������
		exit(0);					// ����������
	}
	return EXIT_SUCCESS;
}
