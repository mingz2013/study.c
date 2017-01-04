/*
 ============================================================================
 Name        : 09_fscanf.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct buddy				// ����ṹ��,���ڱ������ݸ�ʽ
{
	char name[50];
	unsigned int tel;
	char address[200];
};
int main(void) {
	struct buddy bd1;		// �����ṹ�����
	if (creat("buddy", 0664) == -1) {		// ʹ��ϵͳ���ú����������ļ�
		perror("�����ļ�ʧ��");
		return 1;
	}
	FILE *fp;				// �����ļ���ָ��
	fp = fopen("buddy", "rw+");			// ���ļ�
	fprintf(fp, "<name>%s <tel>%d <address>%s ",	// ����ʽ���������������ļ���
			"Tom", 1234567890, "China");
	fclose(fp);				// �ر��ļ�
	fp = fopen("buddy", "rw+");			// �ٴδ��ļ�
	fscanf(fp, "<name>%s <tel>%d <address>%s ", // ��ȡ��ʽ�����ݣ������浽bd1��
			bd1.name, &bd1.tel, bd1.address);
	fclose(fp);
	printf("<name>%s <tel>%d <address>%s ",bd1.name, bd1.tel, bd1.address);

	return EXIT_SUCCESS;
}
