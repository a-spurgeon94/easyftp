#include <iostream>
#include "EasyClient.hpp"
#include <fstream>
using namespace std;
using namespace easysock;

// From http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int main(int argc, char* argv[]) {
	vector<string> args(argv, argv + argc);

	cout << "EasyFTP client" << endl;

	if (args.size() < 2) {
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
			string input;
			getline(cin, input);
			vector<string> params;
			split(input, ' ', params);
			if (params.size() < 1)
				continue;
			
			string command = params[0];

			if (command == "exit")
				break;
			if (command == "dir") {
				socket.WriteString(command);
				cout << "Listing files" << endl;
				cout << socket.ReadString();
			}
			if (command == "cd") {
				if (params.size() < 2) {
					cout << "Missing parameter directory" << endl;
					continue;
				}
				socket.WriteString(input);
				cout << "Changing directory" << endl;
				cout << "Current directory: " << socket.ReadString() << endl;
				cout << endl;
			}
			if (command == "get") {
				if (params.size() < 2) {
					cout << "Missing parameter filename" << endl;
					continue;
				}
				socket.WriteString(input);
				string fileContents = socket.ReadString();
				ofstream filestream(params[1], ios::binary);
				cout << "File successfuly downloaded" << endl;
				filestream << fileContents;
			}
		}
	}
	catch (EasySocketException &e) {
		cout << "Connection error: " << e.what();
		return 1;
	}
	return 0;
}