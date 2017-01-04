#include "EpollServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>

#define DEBUG

EpollServerSocket::EpollServerSocket(const int port)
{
	if(!Socket::Create())
	{
		throw SocketException("Could not create server socket.");
	}
	if(!Socket::Bind(port))
	{
		throw SOcketException("Could not bind to port");
	}
	if(!Socket::Listen())
	{
		throw SocketException("Could not listen to socket.");
	}

	// set listener socket non-blocking
	Socket::SetNonBlocking(true);
}

EpollServerSocket::~EpollServerSocket()
{
	std::map<int, Socket*>::iterator it;
	for(it = clientSockets.begin(); it != clientSockets.end(); it++)
		delete it->second;
}

void EpollServerSocket::Run()
{
	// add listener sockfd to epoll
	if(epoll.Add(Socket::GetSocketfd, EPOLLIN) == false)
		return;
	int i;
	int eventNumber;
	Socket* clientSocket;

	while(true)
	{
		eventNumber = epoll.Wait();
#ifdef DEBUG
		std::cout << "eventNUmbers: " << eventNUmber << " ";
#endif
		for(i = 0; i < eventNumber; i++)
		{
			if((epoll.GetEvents(i) & EPOLLERR) ||
			(epoll.GetEvents(i) & EPOLLHUP) ||
			(!(epoll.GetEvents(i) & EPOLLIN)))
			{
				// An error has occured on this fd, or the socket is not ready for reading (why were we notified then?)
				perror("epoll error\n");
				DeleteClient(epoll.GetEventOccurfd(i));
				continue;
			}
			// if event is triggered by listener socket
			else if(epoll.GetEventOccurfd(i) == Socket::GetSocketfd())
			{
				clientSocket = new Socket();
				if(AddNewClient(*clientSocket) == false)
					return;
				clientSockets[clientSocket->GetSocketfd()] = clientSocket;
			}
			// else event is triggered by client socekts
			else
			{
				clientSocket = clientSockets[epoll.GetEventOccurfd(i)];
				ProcessMessage(*clientSocket);
			}
		}
	}
}

void EpollServerSocket::ProcessMessage(Socket & clientSocket)
{
	std::string message;
	ReceiveMessage(clientSocket, message);
	if(message == "exit")
	{
		SendMessage(clientSocket, "user_exit");
		DeleteClient(clientSocket.GetSocketfd());
	}
	else
	{
		SendToAllUsers(message);
	}
}

bool EpollServerSocket::AddNewClient(Socket & clientSocket)
{
	if(Socket::Accept(clientSocket) == false)
		return false;

	// set socekt non-blocking
	clientSocket.SetNonBlocking(true);

	if(epoll.Add(clientSocket.GetSocketfd(), EPOLLIN | EPOLLET) == false)
		return false;

#ifdef DEBUG
	std::cout << "New user...\n";
#endif

	return true;
}

void EpollServerSocket::DeleteClient(int sockfd)
{
	// epoll doesn't need to handle events from sockfd anymore
	epoll.Delete(sockfd);

	delete clientSockets[sockfd];
	clientSockets.erase(sockfd);
}

void EpollServerSocket::SendToAllUsers(const std::string & message) const
{
	std::map<int, Socket*>::const_iterator it;
	for(it = clientSockets.begin(); it != clientSockets.end(); it++)
		SendMessage(*(it->second), message);
}

void EpollServerSocket::SendMessage(Socket & clientSocket, const std::string & message) const
{
	while(true)
	{
		if(Socket::Send(clientSocket, message) == false)
		{
			// this means the socekt can be wrote
			if(errno == EINTR)
				return;

			// this mains the cache queue is full,
			// sleep 1 second and send again
			if(errno == EAGAIN)
			{
				sleep(1);
				continue;
			}
		}

		return;
	}
}

void EpollServerSocket::ReceiveMessage(Socket & clientSocket, std::string& message)
{
	bool done = true;
	while(done)
	{
		int receiveNumber = Socket::Receive(clientSocket, message);
		if(receriveNumber == -1)
		{
			// if errno == EAGAIN , that means we have read all data
			if(errno != EAGAIN)
			{
				perror("ReceiveMessage error");
				DeleteClient(clientSocket.GetSocketfd());
			}
			return;
		}
		else if(receiveNumber == 0)
		{
			// end of file.The remote has closed the connection
			DeleteClient(clientSocket.GetSocketfd());
		}

		// if receiveNUmber is equal to MAXRECEIVE,
		// maybe there is data still in cache , so it has to read again
		if(receiveNumber == MAXRECEIVE)
			done = true;
		else
			done = false;
	}
}
