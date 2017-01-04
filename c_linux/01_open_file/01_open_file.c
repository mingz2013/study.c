/*
 ============================================================================
 Name        : 01_open_file.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		// �ṩopen()����
#include <sys/types.h>	// �ṩmode_t����
#include <sys/stat.h>	// �ṩopen()�����ķ���
#include <unistd.h>		// �ṩclose()����

int main(void) {

	int f;									// ��������f�����ڱ����ļ���ʶ��
	const char *f_path = "test";			// ����·���ַ���
	mode_t f_attrib;						// ����mode_t�ͱ����������ļ�����

	f_attrib = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
											// Ϊumask������ֵ

	f = open(f_path, O_RDONLY);				// ��ֻ����ʽ���ļ�
	if(f == -1){							// �ж��ļ��Ƿ�򿪳ɹ�
		f = open(f_path, O_RDWR | O_CREAT, f_attrib);	// �������ļ�
		if(f != -1){						// �ж��ļ��Ƿ񴴽��ɹ�
			puts("����һ�����ļ�");
		}
		else{
			puts("�޷��������ļ��������˳� ");
			return 1;
		}//
	}
	else{
		puts("�ļ��򿪳ɹ� ");
	}
	close(f);								// �ر��ļ�

	return 0;
}
