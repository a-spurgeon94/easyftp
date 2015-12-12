#include <iostream>
#include "EasySocket.hpp"
#include <string>
using namespace std;
using namespace easysock;

void sendString(EasySocket &s, string data) {
	int size = htonl((long) data.size());
	s.SendBuffer((char*)&size, sizeof(size));
	s.SendBuffer(data.data(), size);
}

int main() {
	try {
		cout << "EasyFTPServer" << endl;
		EasySocket x(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		x.Bind("0.0.0.0", 1234);
		x.Listen();
		while (true) {
			auto b = x.Accept();

			sendString(b, "hello");
		}
	}
	catch (EasySocketException &e) {
		cout << e.what();
	}
}
