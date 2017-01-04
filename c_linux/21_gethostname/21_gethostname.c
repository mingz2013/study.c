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
#include <sys/socket.h>					// 包含套接字相关函数
#include <netinet/in.h>					// 包含AF_INET相关结构
#include <netdb.h>						// 包含读取主机信息的相关函数
#include <unistd.h>
int main(int argc, char *argv[]) {
	char *host;							// 用于保存主机名
	int sockfd;							// 用于保存套接字标识符
	int len, result;
	struct sockaddr_in address;			// 定义套接字地址
	struct hostent *hostinfo;			// 定义主机信息结构
	struct servent *servinfo;			// 定义服务信息结构
	char buffer[128];
	if (argc == 1) {
		host = "localhost";				// 如果没有指定主机名，则置为本机
	} else {
		host = argv[1];
	}
	hostinfo = gethostbyname(host);		// 获取主机信息
	if (!hostinfo) {
		fprintf(stderr, "找不到主机： %s\n", host);
		return 1;
	}
	servinfo = getservbyname("daytime", "tcp");// 获得服务信息
	if (!servinfo) {
		fprintf(stderr, "无daytime服务\n");
		return 1;
	}
	printf("daytime服务端口是：%d\n", ntohs(servinfo -> s_port));// 输出端口信息

	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// 建立套接字

	address.sin_family = AF_INET;			// 定义套接字地址中的域
	address.sin_port = servinfo->s_port;	// 定义套接字端口
	address.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;// 定义套接字地址

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *) &address, len);// 请求连接
	if(result == -1){
		perror("获取数据出错");
		return 1;
	}
	result = read(sockfd, buffer, sizeof(buffer));	// 接受数据
	buffer[result] = '\0';
	printf("读取 %d 字节： %s ", result, buffer);		// 输出数据
	close(sockfd);									// 关闭连接
	return 0;
}
