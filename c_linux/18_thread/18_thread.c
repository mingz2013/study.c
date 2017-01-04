/*
 ============================================================================
 Name        : 18_thread.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *thread_function(void *arg);

int main(void) {
	int res;					// ���ڱ���������
	pthread_t a_thread;			// ���ڱ����߳���Ϣ
	void *thread_result;		// ���ڱ����̷߳���ֵ
	res = pthread_create(&a_thread, NULL, thread_function, NULL);// �����߳�
	if (res != 0) {				// �ж��̴߳����Ƿ�����
		perror("�̴߳���ʧ��");
		exit(EXIT_FAILURE);
	}
	sleep(3);
	printf("ȡ���߳�...\n");
	res = pthread_cancel(a_thread);	// ����ȡ���߳�����
	if (res != 0) {					// �ж��߳�ȡ���Ƿ��д���
		perror("ȡ���߳�ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�ȴ��߳̽���...\n");
	res = pthread_join(a_thread, &thread_result);	// �ȴ��߳̽���
	if (res != 0) {					// �ж��߳̽����Ƿ��д���
		perror("�߳̽���ʧ��");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
	int i, res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	// �����߳�״̬���������ȡ������
	if (res != 0) {
		perror("�����߳�״̬ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�̺߳�����������\n");
	for (i = 0; i < 10; i++) {
		printf("�̺߳�����������(%d)...\n", i);
		sleep(1);
	}
	pthread_exit(0);
}
