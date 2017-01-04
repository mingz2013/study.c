#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 64

extern int errno;

int connectUDP(const char * host, const char * service);
int errexit(const char * format, ...);

#define UNIXEPOCH 2208988800UL

int main(int argc, char * argv[]){
	char * host = "localhost";
	char * service = "time";
	time_t now;
	int s, n;

	switch(argc){
		case 1:
			host = "localhost";
			break;
		case 2:
			host = argv[1];
			break;
		case 3:
			host = argv[1];
			service = argv[2];
		default:
			fprintf(stderr, "usage: UDPTimed[host[port]]\n");
			exit(1);
	}

	s = connectUDP(host, service);

	(void)write(s, MSC, strlen(MSC));

	n = read(s, (char*)&now, sizeof(now));

	if(n < 0)
		errexit("read failed: %s \n", strerror(errno));

	now = ntohl((unsigned long)now);
	now -= UNIXEPOCH;

	printf("%s\n", ctime(&now));
	exit(0);






}