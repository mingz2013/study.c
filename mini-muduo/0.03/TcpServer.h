#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <sys/epoll.h>

#include "Declear.h"
#include "Define.h"
#include "IChannelCallBack.h"

#include <map>

using namespace std;

class TcpServer : public IChannelCallBack
{
public:
	TcpServer();
	~TcpServer();

	void start();

	virtual void OnIn(int sockfd);

private:
	int createAndListen();

	void update(Channel * pChannel, int op);

	int _epollfd;
	int _listenfd;
	struct epoll_event _events[MAX_EVENTS];
	map<int, Channel*> _channels;

};

#endif