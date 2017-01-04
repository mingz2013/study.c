#include "Epoll.h"
#include <stdio.h>
#include <stdlib.h>

Epoll::Epoll()
:fdNumber(0)
{
	// set resource limits respectively
	rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
	if(::setrlimit(RLIMIT_NOFILE, &rt) == -1)
	{
		perror("setrlimit");
		exit(1);
	}
	// create epoll
	epollfd = epoll_create(MAXEPOLLSIZE);
}

bool Epoll::Add(int fd, int eventsOPtion)
{
	// handle readable event, set Edge Triggered
	event.events = eventsOption;	// EPOLLIN | EPOLLET;
	events.data.fd = fd;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event) < 0)
		return false;
	fdNumber++;
	return true;

}

bool Epoll::Delete(const int eventIndex)
{
	if(epoll_ctl(epollfd, EPOLL_CTL_DEL, events[eventIndex].data.fd, &event) < 0)
		return 0;
	fdNumber--;
	return true;
}

int Epoll::Wait()
{
	int EventNumber;
	eventNumber = epoll_wait(epollfd, events, fdNumber, -1);
	if(eventNumber < 0)
	{
		perror("epoll_wait");
		exit(1);
	}
	return eventNumber;
}

int Epoll::GetEventOccurfd(const int eventIndex) const
{
	return events[eventIndex].data.fd;
}

int Epoll::GetEvents(const int eventIndex) const
{
	return events[eventIndex].events;
}
