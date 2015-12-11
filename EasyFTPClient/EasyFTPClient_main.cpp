#include <iostream>
#include "EasyClient.hpp"
using namespace std;
using namespace easysock;

int main() {
	EasySocket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.Connect("74.125.224.72", 80);
	socket.Send(string("GET / HTTP/1.1\nHost: google.com\n\n"));
	std::vector<char> output = socket.Receive();
	cout << output.data();
	cout << "EasyFTPClient" << endl;
}