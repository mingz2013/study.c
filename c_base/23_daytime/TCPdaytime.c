#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define LINELEN 128
extern int errno;

int connectTCP(const char * host, const char * service);
int errexit(const char * format, ...);

int TCPdaytime(const char * host, const char * service);

int main(int argc, char * argv[]){
	char * host = "localhost";
	char * service = "daytime";
	switch(argc){
		case 1:
			host = "localhost";
			break;
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "usage:TCPtimed[host[port]]\n");
			exit(1);
	}

	TCPdaytime(host, service);
	exit(0);

}


TCPdaytime(const char * host, const char * service){
	char buf[LINELEN + 1];
	int s, n;
	s = connectTCP(host, service);


	while((n = read(s, buf, LINELEN)) > 0){
		buf[n] = '\n';
		(void)fputs(buf, stdout);
	}

}









