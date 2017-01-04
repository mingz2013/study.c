/*
 ============================================================================
 Name        : 16_thread.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>			// �����߳̿�
#include <semaphore.h>			// �����ź�����

void *thread_function(void *arg);	// �����̺߳���ԭ��
sem_t bin_sem;						// �����ź�������
#define	WORK_SIZE	1024
char work_area[WORK_SIZE];			// ���幫�õ��ڴ�ռ�
int main(void) {
	int res;
	pthread_t a_thread;				// ���ڱ��洴���̵߳ķ���ֵ
	void *thread_result;			// ���ڽ����߳�ʱ�ķ���ֵ
	res = sem_init(&bin_sem, 0, 0);	// ��������ʼ���ź���
	if (res != 0) {					// �ж��ź��������Ƿ�ɹ�
		perror("��ʼ���ź���ʧ��");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);	// �����߳�
	if (res != 0) {					// �жϴ����߳��Ƿ��д���
		perror("�̴߳���ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("������Ҫ���͵���Ϣ�����롮end���˳�\n");
	while(strncmp("end", work_area, 3) != 0){	// �ж�������Ƿ���end
		fgets(work_area, WORK_SIZE, stdin);		// ����������Ϣ
		sem_post(&bin_sem);						// ���ź�����1
	}
	printf("\n�ȴ��߳̽���...\n");
	res = pthread_join(a_thread, &thread_result);	// �ȴ��߳̽���
	if (res != 0) {									// �ж��߳̽����Ƿ��д���
		perror("�߳̽���ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�߳̽���\n");
	sem_destroy(&bin_sem);							// ����ź���
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg){					// �����̺߳���ϸ��
	sem_wait(&bin_sem);								// �ȴ��ź����仯�����ź�����1
	while(strncmp("end", work_area, 3) != 0){		// �ж��յ�����Ϣ�Ƿ���end
		printf("�յ�%d���ַ�\n", strlen(work_area) - 1); // ����յ���Ϣ���ַ�����
		sem_wait(&bin_sem);							// �ȴ��ź����仯�����ź�����1
	}
	pthread_exit(NULL);								// �����߳�
}
