#include <iostream>
#include "EasySocket.hpp"
#include <string>
using namespace std;
using namespace easysock;

int main(int argc, char* argv[]) {


	try {
		cout << "EasyFTPServer" << endl;
		EasySocket server(AF_INET, ProtocolType::TCP);
		server.Bind("0.0.0.0", 1234);
		server.Listen();
		while (true) {
			EasySocket client = server.Accept();
			while (true) {
				cout << client.ReadString() << endl;
			}
		}
	}
	catch (EasySocketException &e) {
		cout << e.what();
	}
}
