#include <iostream>
#include "EasySocket.hpp"
#include <string>
#include <sstream>
#include <filesystem>
using namespace std;
using namespace easysock;
using namespace std::tr2::sys;

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


	try {
		cout << "EasyFTPServer" << endl;
		EasySocket server(AF_INET, ProtocolType::TCP);
		server.Bind("0.0.0.0", 1234);
		server.Listen();
		while (true) {
			EasySocket client = server.Accept();
			path dir = "c:\\";
			while (true) {
				string input = client.ReadString();
				
				vector<string> params;
				split(input, ' ', params);
				string command = params[0];
				
				if (command == "dir") {
					cout << "Listing files" << endl;
					stringstream files;
					
					for (auto it = directory_iterator(dir); it != directory_iterator(); ++it)
					{
						files << it->path().filename() << endl;
					}
					client.WriteString(files.str());
				}
				if (command == "cd") {
					string newDir = params[1];
					cout << newDir << endl;
					dir /= newDir;
					cout << dir.string() << endl;
					client.WriteString(dir.string());
				}
			}
		}
	}
	catch (EasySocketException &e) {
		cout << e.what();
	}
}
