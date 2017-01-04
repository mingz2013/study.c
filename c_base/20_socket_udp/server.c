#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define LOCALPORT 4567
int main(int argc, char *argv[])
{
	int mysock, len;
	struct sockaddr_in addrserv, addrcli;
	int i = 0;
	char msg[256];
	int addr_len;
	if( (mysock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("error");
		return -1;
	}
	else{
		printf("socket created \n");
		printf("socked id : %d\n", mysock);
	}
	addr_len = sizeof(struct sockaddr_in);
	bzero(&addrserv, sizeof(addrserv));
	addrserv.sin_family = AF_INET;
	addrserv.sin_addr.s_addr = htonl(INADDR_ANY);
	addrserv.sin_port = htons(LOCALPORT);

	if (bind(mysock, (struct sockaddr *) &addrserv, sizeof(addrserv)) < 0)
	{
		perror("connect");
		return -1;
	}
	else{
		printf("bind ok.\n");
		printf("local port : %d \n", LOCALPORT);
	}

	while(1)
	{
		bzero(msg, sizeof(msg));
		printf("recv msg...\n");
		len = recvfrom(mysock, msg, sizeof(msg), 0, (struct sockaddr *) &addrcli, (socklen_t *) &addr_len);
		printf("%d : ", i);
		i++;
		printf("message from : %s \n", inet_ntoa(addrcli.sin_addr));

		printf("message length : %d \n", len);
		printf("message : %s \n\n", msg);
		sendto(mysock, msg, len, 0, (struct sockaddr *) &addrcli, addr_len);
	}
}
