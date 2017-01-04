#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 5678
#define REMOTE_IP "127.0.0.1"

int main(int argc, char * argv[])
{
	int s;
	struct sockaddr_in addr;
	char mybuffer[256];

	if(  (s = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("socket");
        return -1;
	}
	else{
		printf("socket created \n");
		printf("socked id : %d \n", s);
	}
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(REMOTE_IP);

    if (connect(s, (struct sockaddr_in *) &addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(1);
	}
	else{
		printf("connected ok ! \n");
		printf("remote ip : %s \n", REMOTE_IP);
		printf("remote port : %d \n", PORT);
	}

	recv(s, mybuffer, sizeof(mybuffer), 0);
	printf("%s \n", mybuffer);

	while(1)
	{
		bzero(mybuffer, sizeof(mybuffer));
		read(STDIN_FILENO, mybuffer, sizeof(mybuffer));

		if(send(s, mybuffer, sizeof(mybuffer), 0) < 0)
		{
			perror("send");
			exit(1);
		}else{
			bzero(mybuffer, sizeof(mybuffer));
			recv(s, mybuffer, sizeof(mybuffer), 0);
			printf("recived : %s \n", mybuffer);
		}
	}

}
