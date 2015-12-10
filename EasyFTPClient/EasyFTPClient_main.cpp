#include <iostream>
#include <EasySocket.h>
using namespace std;


int main() {
	EasySocket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	socket.Connect("speets.ca", 80);
	cout << "EasyFTPClient" << endl;
}