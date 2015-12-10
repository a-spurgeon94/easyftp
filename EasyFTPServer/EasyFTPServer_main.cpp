#include <iostream>
#include <EasySocket.h>
using namespace std;


int main() {
	cout << "EasyFTPServer" << endl;

	EasySocket server(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.Bind("127.0.0.1", 666, AF_INET);
	server.Listen(1);
	cout << "Waiting for connection!" << endl;
	EasySocket socket = server.Accept();
	cout << "Connection accepted!" << endl;
	cout << socket.Receive().data();
	socket.Send(string("HTTP/1.1 200 OK\r\n\r\nHello!"));
}