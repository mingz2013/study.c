#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 4096

char buf[BUFSIZE];
char serverip[50] = "127.0.0.1";
struct sockaddr_in servaddr;	// 定义服务器端套接字的端点地址结构变量
int clientfd;	// 定义客户端套接字描述符变量clientfd

int main() {
    clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(struct sockaddr_in));    // 将 服务器端点地址结构变量servaddr清空

// 以下代码为服务器端点地址结构变量赋值
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    inet_aton(serverip, &servaddr.sin_addr);    // 赋值IP地址，需将点分十进制IP地址由本机字节顺序转换为网络字节序

    connect(clientfd, servaddr, sizeof(servaddr));
    send(clientfd, data, data_len, 0);
    recv(clientfd, data, data_len, 0);
    close(clientfd);
}