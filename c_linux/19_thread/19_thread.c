/*
 ============================================================================
 Name        : 19_thread.c
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
#define	NUM_THREADS	6			// �����߳�����
void *thread_function(void *arg);
int main(void) {
	int res;
	pthread_t a_thread[NUM_THREADS];	// �����߳�����
	void *thread_result;
	int lots_of_threads;
	for (lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads++) {
		res = pthread_create(&(a_thread[lots_of_threads]), NULL, thread_function, (void *)&lots_of_threads);
				// ����һ���߳�
		if (res != 0) {
			perror("�̴߳���ʧ��");
			exit(EXIT_FAILURE);
		}
		sleep(1);					// ס�߳���Ϣ1��
	}
	printf("�ȴ��߳̽���...\n");
	for (lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
		res = pthread_join(a_thread[lots_of_threads], &thread_result);// �ȴ��߳̽���
		if (res == 0) {
			printf("����һ���߳�\n");
		} else {
			perror("�߳̽���ʧ��");
		}
	}
	printf("�߳�ȫ������");
	return EXIT_SUCCESS;
}

void *thread_function(void *arg){
	int my_number = *(int *)arg;			// �������̴߳��ݵĲ������ò�������ʱ��������
	int rand_num;
	printf("�̺߳��������У�����Ϊ�� %d\n", my_number);
	rand_num = 1 + (int) (9.0 * rand() / (RAND_MAX + 1.0));// ���һ���������1~9֮�����������
	sleep(rand_num);						// �߳�������������ʱ��˯��
	printf("��%d���߳̽���\n", my_number);
	pthread_exit(NULL);						// �����߳�
}
