#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>	// for zero
#include <iostream>

using namespace std;

#define MAX_LINE 100
#define MAX_EVENTS 500
#define MAX_LISTENFD 5

int createAndListen()
{
	int on = 1;
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;


	fcntl(listenfd, F_SETFL, O_NONBLOCK);	// no-block io
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(11111);

	if(-1 == bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
	{
		cout << "bind error, errno: " << errno << endl;
	}

	if(-1 == listen(listenfd, MAX_LISTENFD))
	{
		cout << "listen error, errno: " << errno << endl;
	}

	return listenfd;

}

int main(int args, char **argv)
{
	struct epoll_event ev, events[MAX_EVENTS];
	int listenfd, connfd, sockfd;
	int readlength;
	char line[MAX_LINE];
	struct sockaddr_in cliaddr;
	socklen_t clilen = sizeof(struct sockaddr_in);
	int epollfd = epoll_create(1);
	if(epollfd < 0)
	{
		cout << "epoll_create error, error: " << epollfd << endl;
	}
	listenfd = createAndListen();

	ev.data.fd = listenfd;
	ev.events = EPOLLIN;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);

	for(;;)
	{
		int fds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if(fd == -1)
		{
			cout << "epoll_wait error, errno: " << errno << endl;
			break;
		}
		for(int i = 0; i < fds; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				connfd = accept(listenfd, (sockaddr*)&cliaddr, (socklen_t*)&clilen);
				if(connfd > 0)
				{
					cout << "new connection from "
						 << "[" << inet_ntoa(cliaddr.sin_addr)
						 << ":" << ntohs(cliaddr.sin_port) << "]"
						 << " accept socket fd: " << connfd
						 << endl;
				}
				else
				{
					cout << "accept error, connfd: " << connfd
						 << " errno: " << errno << endl;
				}

				fcntl(connfd, F_SETFL, O_NONBLOCK);	// no-block io
				ev.data.fd = connfd;
				ev.events = EPOLLIN;
				if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev))
				{
					cout << "epoll_ctl error, errno: " << errno << endl;
				}

			}
			else if(events[i].events & EPOLLIN)
			{
				if((sockfd = events[i].data.fd) < 0)
				{
					cout << "EPOLLIN sockfd < 0 error " << endl;
					continue;
				}
				bzero(line, MAX_LINE);
				if((readlength = read(sockfd, line, MAX_LINE)) < 0)
				{
					if(errno == ECONNRESET)
					{
						cout << "ECONNRESET closed socket fd: " << events[i].data.fd << endl;
						close(sockfd);
					}
				}
				else if(readlength == 0)
				{
					cout << "read 0 closed socket fd: " << events[i].data.fd << endl;
					close(sockfd);
				}
				else
				{
					if(write(sockfd, line, readlength) != readlength)
					{
						cout << "error: not finished one time" << endl;
					}
				} // if

			} // if

		} // for

	}// for

	return 0;
}