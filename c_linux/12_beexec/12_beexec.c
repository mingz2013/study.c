/*
 ============================================================================
 Name        : 12_beexec.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// ���ǵ�һ���ļ����������ߣ��ļ���Ϊbeexec.c
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
extern char **environ;					// ����ȫ�ֱ��������ڱ��滷��������Ϣ
int main(int argc, char* argv[]) {
	int i;
	puts("���ִ�в�����");
	for(i = 0; i <= argc; i++)			// �Գ�������ʱ����Ĳ���������Ϊѭ������
	{
		printf("����%d��:%s\n", i, argv[i]);	// �����е�ִ�в������
	}
	puts("�����������:");
	for (i = 0; environ[i] != NULL; i++) {	// �Ի�������������Ϊѭ������
		printf("%s\n", environ[i]);			// �����л����������
	}
}
