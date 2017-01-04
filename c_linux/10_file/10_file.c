/*
 ============================================================================
 Name        : 10_file.c
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

#define	CTIME	3					// ���������
struct inputvalue					// �ýṹ�屣��ÿ�����������Ϣ
{
	unsigned int length;			// ÿ��������ַ�������
	fpos_t pos;						// ÿ��������ļ��е�λ��
};
int main(void) {
	if (creat("text", 0664) == -1) {		// �����ļ�
		perror("�����ļ�ʧ��");
		return 1;
	}
	struct inputvalue iv[CTIME];	// ������¼������Ϊ�Ľṹ������
	int i;
	FILE *fp;
	fp = fopen("text", "rw+");		// ���ļ�
	for ( i = 0; i < CTIME; i++) {
		fgetpos(fp, &(iv[i].pos));	// ����ָ�뵱ǰλ��
		iv[i].length = fprintf(fp, "��%d�����������", i);	// ������ݵ��ļ�����¼�����Ϣ�ĳ���
	}
	fflush(fp);		// �������������ڵ�����������ļ�
	printf("�ļ����ܳ���Ϊ%ld\n", ftell(fp));	// ��ǰָ���λ��һ�����ļ�β��ָ���ƫ�������ļ�����
	rewind(fp);						// ��ָ������ָ���ļ�ͷ
	for (i = 0; i < CTIME; i++) {
		fsetpos(fp, &(iv[i].pos));	// �������е����ݶ�λָ��
		char *buf = malloc(iv[i].length + 1);	// �������е�������ȼ�1��ֵ��̬���仺������С
		*(buf + iv[i].length + 1) = '\0';	// �����������һλ��Ϊ�ַ����ս��
		fread(buf, iv[i].length, 1, fp);	// ��ȡ������ȵ����ݵ�������
		puts(buf);							// ����������ڵ�����
		free(buf);							// �ͷŻ�����
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
