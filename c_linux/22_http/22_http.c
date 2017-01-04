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
#include <curl/curl.h>					// ����libcurl��
FILE *fp;								// ����һ���ļ���ʶ��
size_t write_data(void *ptr,
		size_t size,
		size_t nmemb,
		void *stream){					// ����ص����������ڽ�HTML�ļ�д�뱾��
	int written = fwrite(ptr, size, nmemb, (FILE *) fp);
	return written;
}

int main(int argc, char *argv[]) {		// ���в�����һ��ΪURL���ڶ���Ϊ�����ļ�·��
	CURL *curl;							// ����CURL��ʶ��ָ��
	curl_global_init(CURL_GLOBAL_ALL);	// ��ʼ��libcurl
	curl = curl_easy_init();			// ����CURL��ʶ��
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);	// ����һ�����в�������ΪҪ���ʵ�URL
	if ((fp = fopen(argv[2], "w")) == NULL) {		// ���ڶ�������������Ϊ·�������ļ�
		puts("������ȷ����ʽ����Ҫ������ļ���");
		curl_easy_cleanup(curl);					// ����ʱ���CURL��ʶ��
		return 1;
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);// ���ûص���������
	curl_easy_perform(curl);		// ��ʼִ�����ݴ��䣬������ִ�лص�
	curl_easy_cleanup(curl);		// ���CURL��ʶ��
	return 0;
}
