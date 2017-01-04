#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket(const std::string & host, const int port)
{
	if(!Socket::Create())
		throw SocketException("Could not create client socket.");
	if(!Socket::Connect(host, port))
		throw SocketException("Could not connect to port.");
}

ClientSocket::~ClientSocket()
{}

bool ClientSocket::Send(const std::string & message)
{
	// 这里使用了dynamic_cast 来将this指针向下转型，转成指向基类Socket的指针
	return Socket::Send(static_cast<Socket&>(*this), message);
}

bool ClientSocket::Receive(std::string & message)
{
	return Socket::Receive(static_cast<Socket&>(*this), message);
}
