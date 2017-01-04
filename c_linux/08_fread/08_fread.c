/*
 ============================================================================
 Name        : 08_fread.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define	SIZE	65536			// ���ڶ��建������С��64KB
#define	LENGTH	1024			// ���ڶ���ÿ�ζ�ȡ�ĳ��ȣ�1KB
int main(void) {
	char buf[SIZE] = {0};		// ���建����
	FILE *fp;					// �����ļ���ָ��
	fp = fopen("/usr/include/gnu-versions.h", "r");	// ���ļ�
	if(fp != NULL){
		if (fread(buf, LENGTH, SIZE / LENGTH, fp) >= 0) {	// ��ȡ���ݵ�������
			puts("��ȡ�ļ��ɹ�");
		} else {
			perror("��ȡ�ļ�ʧ��");
			return 1;
		}
	}
	else
	{
		perror("���ļ�");
	}
	fclose(fp);					// �رձ���ȡ���ļ�
	fp = fopen("copy", "rw+");	// �Զ�дģʽ���ļ������ļ��������Դ��ڵ�
	if(fp != NULL) {
		if (fwrite(buf, LENGTH, SIZE / LENGTH, fp) >= 0) {	// ���������ڵ�����д���ļ�
			fflush(fp); 		// ��������������д�������д���ļ�
			puts("д���ļ��ɹ�");
		} else {
			perror("д���ļ�ʧ��");
			return 1;
		}
	}
	else {
		perror("���ļ�");
	}
	if (fclose(fp) != -1) {
		puts("�ر��ļ��ɹ�");
	} else {
		perror("�ر��ļ�");
	}
	return EXIT_SUCCESS;
}
