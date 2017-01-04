/*
 ============================================================================
 Name        : 21_gethostname.c
 Author      : MingZz
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>					// �����׽�����غ���
#include <netinet/in.h>					// ����AF_INET��ؽṹ
#include <netdb.h>						// ������ȡ������Ϣ����غ���
#include <unistd.h>
int main(int argc, char *argv[]) {
	char *host;							// ���ڱ���������
	int sockfd;							// ���ڱ����׽��ֱ�ʶ��
	int len, result;
	struct sockaddr_in address;			// �����׽��ֵ�ַ
	struct hostent *hostinfo;			// ����������Ϣ�ṹ
	struct servent *servinfo;			// ���������Ϣ�ṹ
	char buffer[128];
	if (argc == 1) {
		host = "localhost";				// ���û��ָ��������������Ϊ����
	} else {
		host = argv[1];
	}
	hostinfo = gethostbyname(host);		// ��ȡ������Ϣ
	if (!hostinfo) {
		fprintf(stderr, "�Ҳ��������� %s\n", host);
		return 1;
	}
	servinfo = getservbyname("daytime", "tcp");// ��÷�����Ϣ
	if (!servinfo) {
		fprintf(stderr, "��daytime����\n");
		return 1;
	}
	printf("daytime����˿��ǣ�%d\n", ntohs(servinfo -> s_port));// ����˿���Ϣ

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// �����׽���

	address.sin_family = AF_INET;			// �����׽��ֵ�ַ�е���
	address.sin_port = servinfo->s_port;	// �����׽��ֶ˿�
	address.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;// �����׽��ֵ�ַ

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *) &address, len);// ��������
	if(result == -1){
		perror("��ȡ���ݳ���");
		return 1;
	}
	result = read(sockfd, buffer, sizeof(buffer));	// ��������
	buffer[result] = '\0';
	printf("��ȡ %d �ֽڣ� %s ", result, buffer);		// �������
	close(sockfd);									// �ر�����
	return 0;
}
