#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

int main()
{
	cout << "Running client..." << endl;
	try
	{
		ClientSocket clientSocket("127.0.0.1", 8080);
		clientSocket.Send("Hello, here is client.");
		string message;
		clientSocket.Receive(message);
		cout << "Response from server:" << message << endl;
	}
	catch(SocketException & ex)
	{
		cout << "Exception was caught:" << ex.Description() << "\n";
	}
	return 0;
}
