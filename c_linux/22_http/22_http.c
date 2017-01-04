/*
 ============================================================================
 Name        : 22_http.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>					// 包含libcurl库
FILE *fp;								// 定义一个文件标识符
size_t write_data(void *ptr,
		size_t size,
		size_t nmemb,
		void *stream){					// 定义回调函数，用于将HTML文件写入本地
	int written = fwrite(ptr, size, nmemb, (FILE *) fp);
	return written;
}

int main(int argc, char *argv[]) {		// 运行参数第一个为URL，第二个为本地文件路径
	CURL *curl;							// 定义CURL标识符指针
	curl_global_init(CURL_GLOBAL_ALL);	// 初始化libcurl
	curl = curl_easy_init();			// 创建CURL标识符
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);	// 将第一个运行参数设置为要访问的URL
	if ((fp = fopen(argv[2], "w")) == NULL) {		// 将第二个参数设置作为路径创建文件
		puts("请以正确的形式输入要保存的文件名");
		curl_easy_cleanup(curl);					// 错误时清除CURL标识符
		return 1;
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);// 设置回调函数名称
	curl_easy_perform(curl);		// 开始执行数据传输，结束后执行回调
	curl_easy_cleanup(curl);		// 清除CURL标识符
	return 0;
}
