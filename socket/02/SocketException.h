#ifndef SocketException_H
#define SocketException_H

#include <string>

class SocketException
{
	public:
		SocketException(std::string description) : m_description (description) {};
		~SocketException () {};

		std::string Description () {return m_description; }

	private:

		std::string m_description;
}

#endif
