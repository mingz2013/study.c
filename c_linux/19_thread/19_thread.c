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
#define	NUM_THREADS	6			// 定义线程总数
void *thread_function(void *arg);
int main(void) {
	int res;
	pthread_t a_thread[NUM_THREADS];	// 定义线程数组
	void *thread_result;
	int lots_of_threads;
	for (lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads++) {
		res = pthread_create(&(a_thread[lots_of_threads]), NULL, thread_function, (void *)&lots_of_threads);
				// 创建一个线程
		if (res != 0) {
			perror("线程创建失败");
			exit(EXIT_FAILURE);
		}
		sleep(1);					// 住线程休息1秒
	}
	printf("等待线程结束...\n");
	for (lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
		res = pthread_join(a_thread[lots_of_threads], &thread_result);// 等待线程结束
		if (res == 0) {
			printf("结束一个线程\n");
		} else {
			perror("线程结束失败");
		}
	}
	printf("线程全部结束");
	return EXIT_SUCCESS;
}

void *thread_function(void *arg){
	int my_number = *(int *)arg;			// 接受主线程传递的参数，该参数可以时任意类型
	int rand_num;
	printf("线程函数已运行，参数为： %d\n", my_number);
	rand_num = 1 + (int) (9.0 * rand() / (RAND_MAX + 1.0));// 获得一个随机数（1~9之间的正整数）
	sleep(rand_num);						// 线程以随机数定义的时间睡眠
	printf("第%d个线程结束\n", my_number);
	pthread_exit(NULL);						// 结束线程
}
