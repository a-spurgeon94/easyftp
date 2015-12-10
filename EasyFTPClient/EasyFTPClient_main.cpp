#include <iostream>
#include <EasySocket.h>
using namespace std;


int main() {
	EasySocket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.Connect("74.125.224.72", 80);
	std::string msg = "GET / HTTP/1.1\nHost: google.com\n\n";
	std::vector<char> bytes(msg.begin(), msg.end());
	socket.Send(bytes);
	std::vector<char> output = socket.Receive();
	cout << output.data();
	cout << "EasyFTPClient" << endl;
}