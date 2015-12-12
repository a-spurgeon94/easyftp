#include <iostream>
#include "EasySocket.hpp"
#include <string>
using namespace std;
using namespace easysock;

int main() {
	try {
		cout << "EasyFTPServer" << endl;
		EasySocket server(AF_INET, ProtocolType::TCP);
		server.Bind("0.0.0.0", 1234);
		server.Listen();
		while (true) {
			EasySocket client = server.Accept();

			client.WriteString("hello");
		}
	}
	catch (EasySocketException &e) {
		cout << e.what();
	}
}
