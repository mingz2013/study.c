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
pthread_mutex_t work_mutex;			// ���廥����
#define	WORK_SIZE	1024
char work_area[WORK_SIZE];			// ���幫�õ��ڴ�ռ�
int time_to_exit = 1;				// ���ڿ���ѭ��
int main(void) {
	int res;
	pthread_t a_thread;				// ���ڱ��洴���̵߳ķ���ֵ
	void *thread_result;			// ���ڽ����߳�ʱ�ķ���ֵ
	res = pthread_mutex_init(&work_mutex, NULL);	// ��������ʼ��������
	if (res != 0) {					// �жϻ����������Ƿ�ɹ�
		perror("��ʼ��������ʧ��");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);	// �����߳�
	if (res != 0) {					// �жϴ����߳��Ƿ��д���
		perror("�̴߳���ʧ��");
		exit(EXIT_FAILURE);
	}
	pthread_mutex_lock(&work_mutex);			// ����������
	printf("������Ҫ���͵���Ϣ�����롮end���˳�\n");
	while(time_to_exit){						// �ж�ѭ����־״̬
		fgets(work_area, WORK_SIZE, stdin);		// ����������Ϣ
		pthread_mutex_unlock(&work_mutex);		// ����������
		while(1){
			pthread_mutex_lock(&work_mutex);	// ����������
			if (work_area[0] != '\0') {			// �жϹ����ڴ�ռ��Ƿ�Ϊ��
				pthread_mutex_unlock(&work_mutex);	// ����������
				sleep(1);						// ԭ���߳�˯��1��
			} else {
				break;							// ����ѭ��
			}
		}
	}
	pthread_mutex_unlock(&work_mutex);			// ����������
	printf("\n�ȴ��߳̽���...\n");
	res = pthread_join(a_thread, &thread_result);	// �ȴ��߳̽���
	if (res != 0) {									// �ж��߳̽����Ƿ��д���
		perror("�߳̽���ʧ��");
		exit(EXIT_FAILURE);
	}
	printf("�߳̽���\n");
	pthread_mutex_destroy(&work_mutex);							// ���������
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg){					// �����̺߳���ϸ��
	sleep(1);										// ���߳�˯��1��
	pthread_mutex_lock(&work_mutex);								// �����ź���
	while(strncmp("end", work_area, 3) != 0){		// �ж��յ�����Ϣ�Ƿ���end
		printf("�յ�%d���ַ�\n", strlen(work_area) - 1); // ����յ���Ϣ���ַ�����
		work_area[0] = '\0';						// �������ռ����
		pthread_mutex_unlock(&work_mutex);			// ����������
		sleep(1);									// ���߳�˯��1��
		pthread_mutex_lock(&work_mutex);			// ����������
		while(work_area[0] == '\0'){				// �жϹ����ռ��Ƿ�Ϊ��
			pthread_mutex_unlock(&work_mutex);		// ����������
			sleep(1);								// ���߳�˯��1��
			pthread_mutex_lock(&work_mutex);		// ����������
		}
	}
	time_to_exit = 0;								// ��ѭ��������־��Ϊ0
	work_area[0] = '\0';							// ��������ռ�
	pthread_mutex_unlock(&work_mutex);				// ����������
	pthread_exit(0);								// �����߳�
}
