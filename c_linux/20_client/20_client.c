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
#include <sys/socket.h>					// 包含套接字函数库
#include <netinet/in.h>					// 包含AF_INET相关结构
#include <arpa/inet.h>					// 包含AF_INET相关操作的函数
#include <unistd.h>

int main(void) {
	int sockfd;							// 用于保存客户端套接字标识符
	int len;							// 用于保存客户端消息长度
	struct sockaddr_in address;			// 定义客户端套接字地址
	int result;
	char ch = 'A';						// 定义要传送的消息

	sockfd = socket(AF_INET, SOCK_STREAM, 0);// 定义套接字类型

	address.sin_family = AF_INET;		// 定义套接字地址中的域
	address.sin_addr.s_addr = inet_addr("127.0.0.1");// 定义套接字地址
	address.sin_port = 9734;			// 定义套接字端口

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *) &address, len);// 请求连接
	if (result == -1) {
		perror("链接失败");
		return 1;
	}
	write(sockfd, &ch, 1);				// 向服务器传送消息
	read(sockfd, &ch, 1);				// 从服务器接受消息
	printf("来自服务器的消息是 %c \n", ch);
	close(sockfd);						// 关闭连接
	return 0;
}
