/*
 ============================================================================
 Name        : 15_pthread.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>					// �����߳̿�
#include <string.h>

void *thread_function(void *arg);		// �����̺߳���ԭ��
char message[] = "THREAD_TEST";			// ���幫�õ��ڴ�ռ�

int main(void) {
	int res;							// ���ڱ��洴���̵߳ķ���ֵ
	pthread_t a_thread;					// ���ڱ����̱߳�ʶ������Ϣ
	void *thread_reasult;				// ���ڽ����߳̽����ǵķ���ֵ
	res = pthread_create(&a_thread, NULL, thread_function, (void*) message);
										// �����߳�
	if(res != 0) {						// �жϴ����߳��Ƿ��д���
		perror("�̴߳���ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�ȴ��߳̽���...\n");
	res = pthread_join(a_thread, &thread_reasult);	// �ȴ��߳̽���
	if (res != 0) {									// �жϽ����߳��Ƿ��д���
		perror("�ȴ��߳̽���ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�߳��ѽ���������ֵ�� %s\n", (char *)thread_reasult);	// ����̷߳��ص���Ϣ
	printf("Message��ֵΪ�� %s\n", message);			// ������õ��ڴ�ռ��ֵ
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {					// �����̺߳���ϸ��
	printf("�߳������У�����Ϊ�� %s\n", (char*)arg);	// ����̵߳Ĳ���
	sleep(3);										// ʹ�߳�����3��
	strcpy(message, "�߳��޸�");						// �޸Ĺ��õ��ڴ�ռ��ֵ
	pthread_exit("�߳�ִ�����");						// �����߳�
}
