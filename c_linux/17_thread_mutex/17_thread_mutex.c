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
#include <pthread.h>			// 包含线程库
#include <semaphore.h>			// 包含信号量库

void *thread_function(void *arg);	// 定义线程函数原型
pthread_mutex_t work_mutex;			// 定义互斥量
#define	WORK_SIZE	1024
char work_area[WORK_SIZE];			// 定义公用的内存空间
int time_to_exit = 1;				// 用于控制循环
int main(void) {
	int res;
	pthread_t a_thread;				// 用于保存创建线程的返回值
	void *thread_result;			// 用于接受线程时的返回值
	res = pthread_mutex_init(&work_mutex, NULL);	// 创建并初始化互斥量
	if (res != 0) {					// 判断互斥量创建是否成功
		perror("初始化互斥量失败");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);	// 创建线程
	if (res != 0) {					// 判断创建线程是否有错误
		perror("线程创建失败");
		exit(EXIT_FAILURE);
	}
	pthread_mutex_lock(&work_mutex);			// 锁定互斥量
	printf("请输入要传送的信息，输入‘end’退出\n");
	while(time_to_exit){						// 判断循环标志状态
		fgets(work_area, WORK_SIZE, stdin);		// 接受输入信息
		pthread_mutex_unlock(&work_mutex);		// 解锁互斥量
		while(1){
			pthread_mutex_lock(&work_mutex);	// 锁定互斥量
			if (work_area[0] != '\0') {			// 判断公共内存空间是否为空
				pthread_mutex_unlock(&work_mutex);	// 解锁互斥量
				sleep(1);						// 原有线程睡眠1秒
			} else {
				break;							// 结束循环
			}
		}
	}
	pthread_mutex_unlock(&work_mutex);			// 解锁互斥量
	printf("\n等待线程结束...\n");
	res = pthread_join(a_thread, &thread_result);	// 等待线程结束
	if (res != 0) {									// 判断线程结束是否有错误
		perror("线程结束失败");
		exit(EXIT_FAILURE);
	}
	printf("线程结束\n");
	pthread_mutex_destroy(&work_mutex);							// 清除互斥量
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg){					// 定义线程函数细节
	sleep(1);										// 子线程睡眠1秒
	pthread_mutex_lock(&work_mutex);								// 锁定信号量
	while(strncmp("end", work_area, 3) != 0){		// 判断收到的信息是否是end
		printf("收到%d个字符\n", strlen(work_area) - 1); // 输出收到信息的字符数量
		work_area[0] = '\0';						// 将公共空间清除
		pthread_mutex_unlock(&work_mutex);			// 解锁互斥量
		sleep(1);									// 子线程睡眠1秒
		pthread_mutex_lock(&work_mutex);			// 锁定互斥量
		while(work_area[0] == '\0'){				// 判断公共空间是否为空
			pthread_mutex_unlock(&work_mutex);		// 解锁互斥量
			sleep(1);								// 子线程睡眠1秒
			pthread_mutex_lock(&work_mutex);		// 锁定互斥量
		}
	}
	time_to_exit = 0;								// 将循环结束标志置为0
	work_area[0] = '\0';							// 清除公共空间
	pthread_mutex_unlock(&work_mutex);				// 解锁互斥量
	pthread_exit(0);								// 结束线程
}
