/*
 ============================================================================
 Name        : 20_server.c
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
	int server_sockfd, client_sockfd;	// ���ڱ���������Ϳͻ����׽��ֱ�ʶ��

	int server_len, client_len;			// ���ڱ���������Ϳͻ�����Ϣ����

	struct sockaddr_in server_address;	// ����������׽��ֵ�ַ
	struct sockaddr_in client_address;	// ����ͻ����׽��ֵ�ַ

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);	// �����׽�������

	server_address.sin_family = AF_INET;	// �����׽��ֵ�ַ�е���
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");// �����׽��ֵ�ַ
	server_address.sin_port = 9734;		// �����׽��ֶ˿�

	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
										// �����׽�������
	listen(server_sockfd, 5);			// �����׽��ֶ���
	while(1)
	{
		char ch;
		printf("�������ȴ���Ϣ\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *__restrict) &client_len);
										// ��������
		read(client_sockfd, &ch, 1);	// ��ȡ�ͻ���Ϣ
		ch++;
		write(client_sockfd, &ch, 1);	// ��ͻ��˴�����Ϣ
		close(client_sockfd);			// �ر�����
	}
}
