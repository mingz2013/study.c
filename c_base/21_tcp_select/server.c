#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5678
#define MAX 10

int main()
{
	int sockfd, newsockfd, is_connected[MAX], fd;
	struct sockaddr_in addr;
	int addr_len = sizeof(struct sockaddr_in);
	fd_set myreadfds;
	char msgbuffer[256];
	char msg[] = "This is the message from server. Connected. \n";

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("socket");
		return -1;
	}else{
		printf("socket created \n");
		printf("socket id : %d \n", sockfd);
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		perror("connect");
		return -1;
	}else{
		printf("connected \n");
		printf("local port : %d\n", PORT);
	}
	if(listen(sockfd, 3) < 0)
	{
		perror("listen");
		return -1;
	}else{
		printf("listenning...\n");
	}
	for(fd = 0; fd < MAX; fd++)
	{
		is_connected[fd] = 0;
	}
	while(1)
	{
		FD_ZERO(&myreadfds);
		FD_SET(sockfd, &myreadfds);

		for(fd = 0; fd < MAX; fd++)
		{
			if(is_connected[fd])
			{
				FD_SET(fd, &myreadfds);
			}
		}

		if(!select(MAX, &myreadfds, NULL, NULL, NULL))
		{
			continue;
		}
		for(fd = 0; fd < MAX; fd++)
		{
			if(FD_ISSET(fd, &myreadfds))
			{
				if(sockfd  == fd)
				{
					if ((newsockfd = accept(sockfd, (struct sockaddr *) &addr, (socklen_t *) &addr_len)) < 0)
					{
						perror("accept");
					}
					write(newsockfd, msg, sizeof(msg));
					is_connected[newsockfd] = 1;
					printf("connect from %s \n", inet_ntoa(addr.sin_addr));
				}else
				{
					bzero(msgbuffer, sizeof(msgbuffer));
					if(read(fd, msgbuffer, sizeof(msgbuffer)) <= 0)
					{
						printf("connect closed \n");
						is_connected[fd] = 0;
						close(fd);
					}else{
						write(fd, msgbuffer, sizeof(msgbuffer));
						printf("message : %s \n", msgbuffer);
					}
				}
			}
		}

	}

}
