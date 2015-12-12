#include <iostream>
#include "EasyClient.hpp"
using namespace std;
using namespace easysock;

int main() {
	EasySocket socket(AF_INET, ProtocolType::TCP);
	socket.Connect("127.0.0.1", 1234);	
	cout << socket.ReadString() << endl;
}