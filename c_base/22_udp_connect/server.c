#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 4096 // 定义缓冲区大小为4MB
char buf[BUFSIZE];	// 定义缓冲区变量buf
struct sockaddr_in servaddr, clientaddr;	// 定义服务器端和客户端套接字的端点地址结构变量
int serverfd, newclientfd;	// 定义服务器端主套接字 和 从套接字描述符变量

int main() {
    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&serveraddr, sizeof(struct sockaddr_in));    // 将服务器端点地址结构变量servaddr清空

// 以下代码段实现为服务器端点地址结构变量servaddr赋值
    servaddr.sin_family = AF_INET;    // 赋值协议族为TCP/IP协议族
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);    // 赋值IP地址为符号常量INADDR_ANY,需要将符号常量INADDR_ANY由本机字节序转换为网络字节序
    servaddr.sin_port = htons(SERVER_PORT);    // 赋值端口号，需将端口号由本机字节序转换为网络字节序

    bind(serverfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in));
    listen(serverfd, 20);
    newclientfd = accept(sockfd, (struct sockaddr *) &clientaddr, sizeof(clientaddr));
    recv(newclientfd, buf, sizeof(buf), 0);
    send(newclientfd, buf, strlen(buf), 0);
    close(newclientfd);
}
