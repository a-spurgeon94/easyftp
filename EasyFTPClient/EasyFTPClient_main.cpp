#include <iostream>
#include "EasyClient.hpp"
using namespace std;
using namespace easysock;

int main() {
	cout << "EasyFTPClient\n" << endl;

	EasySocket socket(AF_INET, ProtocolType::TCP);
	socket.Connect("172.21.24.100", 666);
	socket.Send(string("GET / HTTP/1.1\nHost: google.com\n\n"));
	std::vector<char> output = socket.Receive();
	cout << output.data();


	EasyClient client(666);
	client.Connect("127.0.0.1");
	//client.Send("Hello");
	//client.Send(42);
}