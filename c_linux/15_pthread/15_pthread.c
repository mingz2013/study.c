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
#include <pthread.h>					// 包含线程库
#include <string.h>

void *thread_function(void *arg);		// 定义线程函数原型
char message[] = "THREAD_TEST";			// 定义公用的内存空间

int main(void) {
	int res;							// 用于保存创建线程的返回值
	pthread_t a_thread;					// 用于保存线程标识符等信息
	void *thread_reasult;				// 用于接受线程结束是的返回值
	res = pthread_create(&a_thread, NULL, thread_function, (void*) message);
										// 创建线程
	if(res != 0) {						// 判断创建线程是否有错误
		perror("线程创建失败");
		exit(EXIT_FAILURE);
	}
	printf("等待线程结束...\n");
	res = pthread_join(a_thread, &thread_reasult);	// 等待线程结束
	if (res != 0) {									// 判断结束线程是否有错误
		perror("等待线程结束失败");
		exit(EXIT_FAILURE);
	}
	printf("线程已结束，返回值： %s\n", (char *)thread_reasult);	// 输出线程返回的消息
	printf("Message的值为： %s\n", message);			// 输出公用的内存空间的值
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {					// 定义线程函数细节
	printf("线程在运行，参数为： %s\n", (char*)arg);	// 输出线程的参数
	sleep(3);										// 使线程休眠3秒
	strcpy(message, "线程修改");						// 修改公用的内存空间的值
	pthread_exit("线程执行完毕");						// 结束线程
}
