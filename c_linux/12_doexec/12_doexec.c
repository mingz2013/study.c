/*
 ============================================================================
 Name        : 12_doexec.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
// ���ǵڶ����ļ��������ߣ��ļ���Ϊdoexec.c
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
extern char **environ;					// ����ȫ�ֱ��������ڱ��滷��������Ϣ
int main(int argc, char* argv[]) {
	puts("����Ϣ�����޷����");
	execve("beexec", argv, environ);	// ��beexec�����滻����ִ��ӳ��
	puts("��������´���Ϣ�޷����");
}
