#include <iostream>
#include "EasyClient.hpp"
using namespace std;
using namespace easysock;

string recvString(EasySocket &socket) {
	int size = htonl((int&)*socket.Receive(4).data());
	vector<char> dataVec = socket.Receive(size);
	string out(dataVec.data(), size);
	return out;
}

int main() {
	EasySocket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.Connect("127.0.0.1", 1234);	
	cout << recvString(socket) << endl;
}