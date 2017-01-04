#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>	// 该头文件中定义了与网络有关的结构，变量类型，宏，函数，如gethostbyname

extern int errno;
int errexit(const char * format, ...);
unsigned int portbase = 0;	// 定义全局变量portbase,

int passivesock(const char * service, const char * transport, int qlen){
	struct servent * pse;	// 用于保存getservbyname() 函数 返回值
	struct portoent * ppe;	// 保存 getprotobyname 返回值
	struct sockaddr_in sin;	// 定义服务器端套接字的端点地址结构变量sin
	int s, type;	// 服务器端套接字描述符s和套接字提供的服务类型type
	memset(&sin, 0, sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	if(pse = getservbyname(service, transport))
		sin.sin_port = htons(ntohs((unsigned short)pse->s_port) + portbase);
	else if((sin.sin_port = htons((unsigned short)atoi(service)) == 0))
		errexit("can't get \" %s \" service entry \n", service);

	if((ppe = getprotobyname(transport)) == 0)
		errexit("can't get \" %s \" protocol entry \n", transport);

	if(strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	s = socket(PF_INET, type, ppe->p_proto);	// 调用socket创建服务器端套接字
	if(s < 0)
		errexit("can't create socket: %s\n", strerror(errno));
	if(bind(s, (struct sockaddr*)&sin, sizeof(sin)) < 0)
		errexit("can't bind to %s port: %s \n", service, strerror(errno));
	if(type == SOCK_STREAM && listen(s, qlen) < 0)
		errexit("can't listen on %s port: %s \n", service, strerror(errno));

	return s;


}