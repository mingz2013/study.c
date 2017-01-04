// 该服务器例程 能够反复读取来自客户的任何请求，且一旦受到了客户端的请求后，则计算出服务器的当前时间，并将该时间值作为响应回送给发送请求的那个客户

#include <sys/types.h> // 该头文件中定义了各种数据类型
#include <sys/socket.h> // 该头文件中包含套接字API中系统函数的定义
#include <netinet/in.h>	// 该头文件中定义了数据结构sockaddr_in
#include <stdio.h>	// 标准输入输出函数所在的头文件
#include <time.h>	// 该头文件包含了有关时间计算的各类函数
#include <strings.h>	// 该头文件包含了strerror() 函数的定义
#include <errno.h>	// 该头文件中包含了全局变量errno的定义

extern int errno;	// 外部全局变量errno记录了系统函数出错时的错误编号
int passiveUDP(const char * service);	// 声明用于建立被动UDP套接字的子函数
int errexit(const char * format, ...);	// 声明用于输出不同格式的出错信息的可变参数子函数

#define UNIXEPOCH 2208988800UL	// 定义UNIX系统的时间纪元常量
#define MSC "what time is it? \n"	// 定义符号常量MSC

int main(int argc, char *argv[]){
	struct sockaddr_in fsin;	// 定义服务器套接字的端点地址结构变量fsin
	char * service = "time";	// 定义用于存储服务名的变量
	char buf[1];	// 定义变量buf以存储来自客户的请求
	int sock;	// 定义服务器端套接字描述符变量sock
	time_t now;	// 定义用于存储当前时间的变量now
	unsigned int alen;	// 定义用于存储服务器端点地址结构长度的变量alen

	switch(argc){	// 判断命令行输入的参数的个数
		case 1: break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: server [port] \n");
	}

	sock = passiveUDP(service);	// 调用。。。建立UDP被动套接字

	while(1){
		alen = sizeof(fsin);
		if(recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&fsin, &alen) < 0)	// 接受一个来自客户的请求时出错，显示出错信息并退出
			errexit("recvfrom: %s\n", strerror(errno));
		(void)time(&now);	// 获取当前时间
		now = htonl((unsigned long)(now + UNIXEPOCH));	// 将Linux服务器当前时间转换为用因特网纪元测量的时间值

		(void)sendto(sock, (char*)&now, sizeof(now), 0, (struct sockaddr*)&fsin, sizeof(fsin));	// 发送给客户
	}


	return 0;
}