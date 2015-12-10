#include "EasySocket.h"

/** @file EasySocket.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Wrapper implementation for the Socket library API
*/

// Constructor
EasySocket::EasySocket(int addressFamily, int type, int protocol) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw new std::exception("WSAStartup has failed");

	hSocket = socket(addressFamily, type, protocol);

	if (hSocket == INVALID_SOCKET) {
		throw new std::exception("socket has failed");
	}

	socketAddress = { 0 };
	socketAddress.sin_family = addressFamily;
	// Use 'printable to network', inet_addr deprecated.
	inet_pton(addressFamily, "127.0.0.1", &(socketAddress.sin_addr));

}

// Destructor
EasySocket::~EasySocket() {
	cleanSocket();	
	cleanWSA(); 
}

void EasySocket::Connect(std::string host, int port) {
	// Create the server address
	socketAddress.sin_port = htons(port);
	inet_pton(AF_INET, host.c_str(), &socketAddress.sin_addr.s_addr);

	// connect the socket
	if (connect(hSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress)) == SOCKET_ERROR) {
		throw new std::exception("Connect has failed");
	}
}

std::vector<char> EasySocket::Receive(int flags) {
	std::vector<char> buffer(1024);
	buffer.resize(recv(hSocket, buffer.data(), buffer.size(), flags));
	return buffer;
}

// --------------------------------- //
//         Private Functions         //
// --------------------------------- //

void EasySocket::cleanSocket() {
	closesocket(hSocket);	// Close socket handle
}

void EasySocket::cleanWSA() {
	WSACleanup();			// Clean up WSA information
}