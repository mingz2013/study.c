/*
 ============================================================================
 Name        : 05_read_write_file.c
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

#define	LENGTH 2000					// �ڴ����󳤶�
int main(void) {
	char c[LENGTH];					// �����ڴ��
	int f, i, j = 0;
	f = open("/usr/include/gnu-versions.h", // ��ָ��·���ļ�
			O_RDONLY,						// �򿪷�ʽΪֻ��
			LENGTH							// ÿ�ζ��뵽���������ֽ�Ϊ2000
			);
	if(f != -1){							// �ж��ļ��Ƿ�򿪳ɹ�
		i = read(f, c, LENGTH);				// ���ļ���ȡָ�����ȵ����ݣ���ʵ�ʳ��ȸ�ֵ��i
		if(i > 0){							// �ж��Ƿ���ȷ��ȡ
			for( ; i > 0; i--)				// ��ʵ�ʳ�����Ϊѭ������
			{
				putchar(c[j++]);			// ���ָ��λ�õ��ַ�
			}
		}
		else{
			perror("��ȡ");					// ���������Ϣ
		}

	}
	else{
		perror("���ļ�");
	}

	return 0;
}
