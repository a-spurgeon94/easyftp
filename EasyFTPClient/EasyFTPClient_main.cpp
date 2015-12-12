#include <iostream>
#include "EasyClient.hpp"
using namespace std;
using namespace easysock;

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);

	cout << "EasyFTP client" << endl;

	if (args.size() < 1) {
		cout << "Error: Missing ip address parameter" << endl;
		cout << endl;
		cout << "Usage: " << args[0] << " [ip-address]" << endl;
		return 1;
	}

	string host = args[1];

	EasySocket socket(AF_INET, ProtocolType::TCP);

	try {	
		socket.Connect(host, 1234);
	}
	catch (EasySocketException &e) {
		cout << "Unable to connect to " << host << ": " << e.what() << endl;
		return 1;
	}

	cout << "Connected to " << host << endl;
	
	try {
		while (true) {
			cout << "> ";
			string command;
			getline(cin, command);
			if (command == "exit")
				break;
			socket.WriteString(command);
		}
	}
	catch (EasySocketException &e) {
		cout << "Connection error: " << e.what();
		return 1;
	}
	return 0;
}