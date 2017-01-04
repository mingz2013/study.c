#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#define REMOTEPORT 4567	// 定义表示端口号的常量
#define REMOTEIP "127.0.0.1"	// 定义表示IP地址的常量
int main(int argc, char *argv[])
{
	int s, len;
	struct sockaddr_in addr;
	int addr_len;
	char msg[256];
	int i = 0;
	if( (s = socket(AF_INET, SOCK_DGRAM, 0) ) < 0 )
	{
		perror("error");
		return -1;
	}
	else{
		printf("socket created \n");
		printf("socked id : %d \n", s);
		printf("remote ip: %s\n", REMOTEIP);
		printf("remote port : %d \n", REMOTEPORT);
	}
    addr_len = sizeof(struct sockaddr_in);
	len = sizeof(struct sockaddr_in);// 长度
	bzero(&addr, sizeof(addr));	// 空间地址结构体所在的内存空间
	addr.sin_family = AF_INET;	// 填充地址与端口信息
	addr.sin_port = htons(REMOTEPORT);	// 端口
	addr.sin_addr.s_addr = inet_addr(REMOTEIP);
//
//	if(connect(s, (struct sockaddr *)&addr, addr_len) == -1)
//	{
//		perror("connect error");
//		exit(1);
//	}

	while(1)
	{
		bzero(msg, sizeof(msg));	// 清空msg所在内存
		len = read(STDIN_FILENO, msg, sizeof(msg));	// 接受信息
        printf("len: %d\n", len);
        printf("msg: %s\n", msg);
		sendto(s, msg, len, 0, (struct sockaddr *) &addr, addr_len);    // 发送信息
		printf("\n Input message: %s \n", msg);	// 输出结果
		len = recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *) &addr, (socklen_t *) &addr_len);    // 这是接收到的信息
		printf("%d : ", i);
		i++;
		printf("Received message : %s \n", msg);	// 这是服务器返回的信息
	}


}
