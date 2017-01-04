#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
extern int errno;
int passiveTCP(const char * service);
int errexit(const char * format, ...);

var TCPdaytimed(int fd);	// 声明用于计算出服务器当前时间，并调用write函数通过所建立的临时套接字将改时间值作为响应回送给该客户的子函数

int main(int argc, char*argv[]){
	struct sockaddr_in fsin;
	char * service = "daytime";
	int msock, ssock;

	unsigned int alen;

	switch(argc){
		case 1:break;
		case 2:
			service = argv[1];break;
		default:
		errexit("usage : TCPdaytimed[port\n]");
	}

	msock = passiveTCP(service);
	while(1){
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr*)&fsin, & alen);

		if(ssock < 0)
			errexit("accept failed: %s\n", strerror(errno));

		TCPdaytimed(ssock);

		(void)close(ssock);

	}
	return 0;
}

void TCPdaytimed(int fd){
	char * pts;
	time_t now;
	char * ctime();	// 在函数内部声明ctrime的原型
	(void)time(&now);
	pts = ctime(&now);

	(void)write(fd, pts, strlen(pts));
}










