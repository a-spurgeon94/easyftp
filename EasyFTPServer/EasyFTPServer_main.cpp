#include <iostream>
#include "EasySocket.hpp"
#include <sstream>
#include <filesystem>
using namespace std;
using namespace easysock;
using namespace std::tr2::sys;

int main() {
	cout << "EasyFTPServer" << endl;

	EasySocket server(AF_INET, SOCK_STREAM);
	server.Bind("0.0.0.0", 666);
	server.Listen();
	cout << "Waiting for connection!" << endl;
	size_t count = 0;
	while (true) {
		EasySocket socket = server.Accept();
		cout << "Connection accepted!" << endl;
		socket.Receive();
		cout << socket.IpAddress() << endl;
		socket.Send(string("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"));
		stringstream msg;
		msg << "<ul>" << endl;
		for (auto it = directory_iterator("."); it != directory_iterator(); ++it) {
			msg << "<li><a href=\"#\">" << it->path() << "</a></li>" << endl;
		}
		msg << "</ul>";
		socket.Send(msg.str());
	}
}