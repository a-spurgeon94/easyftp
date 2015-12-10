#include <iostream>
#include <EasySocket.h>
using namespace std;


int main() {
	EasySocket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.Connect("127.0.0.1", 80);
	cout << "EasyFTPClient" << endl;
}