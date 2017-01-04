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
	int res;					// 用于保存操作结果
	pthread_t a_thread;			// 用于保存线程信息
	void *thread_result;		// 用于保存线程返回值
	res = pthread_create(&a_thread, NULL, thread_function, NULL);// 创建线程
	if (res != 0) {				// 判断线程创建是否有误
		perror("线程创建失败");
		exit(EXIT_FAILURE);
	}
	sleep(3);
	printf("取消线程...\n");
	res = pthread_cancel(a_thread);	// 发送取消线程请求
	if (res != 0) {					// 判断线程取消是否有错误
		perror("取消线程失败");
		exit(EXIT_FAILURE);
	}
	printf("等待线程结束...\n");
	res = pthread_join(a_thread, &thread_result);	// 等待线程结束
	if (res != 0) {					// 判断线程结束是否有错误
		perror("线程结束失败");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg)
{
	int i, res;
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	// 定义线程状态，允许接受取消请求
	if (res != 0) {
		perror("定义线程状态失败");
		exit(EXIT_FAILURE);
	}
	printf("线程函数正在运行\n");
	for (i = 0; i < 10; i++) {
		printf("线程函数正在运行(%d)...\n", i);
		sleep(1);
	}
	pthread_exit(0);
}
