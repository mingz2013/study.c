/*
 ============================================================================
 Name        : 07_file.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp;				// �����ļ���ָ��
	fp = fopen("/usr/include/gnu-versions.h", "r");
								// ��ֻ����ʽ���ļ����������ص��ļ���ָ�븳��*fp
	if (fp != NULL) {
		puts("���ļ��ɹ�");
	} else {
		perror("���ļ�");
		return 1;
	}
	if (fclose(fp) != -1) {
		puts("�ر��ļ��ɹ�");
	} else {
		perror("�ر��ļ�");
		return 1;
	}
	return EXIT_SUCCESS;
}
