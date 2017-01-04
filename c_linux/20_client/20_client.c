/*
 ============================================================================
 Name        : 20_client.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>					// �����׽��ֺ�����
#include <netinet/in.h>					// ����AF_INET��ؽṹ
#include <arpa/inet.h>					// ����AF_INET��ز����ĺ���
#include <unistd.h>

int main(void) {
	int sockfd;							// ���ڱ���ͻ����׽��ֱ�ʶ��
	int len;							// ���ڱ���ͻ�����Ϣ����
	struct sockaddr_in address;			// ����ͻ����׽��ֵ�ַ
	int result;
	char ch = 'A';						// ����Ҫ���͵���Ϣ

	sockfd = socket(AF_INET, SOCK_STREAM, 0);// �����׽�������

	address.sin_family = AF_INET;		// �����׽��ֵ�ַ�е���
	address.sin_addr.s_addr = inet_addr("127.0.0.1");// �����׽��ֵ�ַ
	address.sin_port = 9734;			// �����׽��ֶ˿�

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *) &address, len);// ��������
	if (result == -1) {
		perror("����ʧ��");
		return 1;
	}
	write(sockfd, &ch, 1);				// �������������Ϣ
	read(sockfd, &ch, 1);				// �ӷ�����������Ϣ
	printf("���Է���������Ϣ�� %c \n", ch);
	close(sockfd);						// �ر�����
	return 0;
}
