#include "EasySocket.h"

/** @file EasySocket.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Wrapper implementation for the Socket library API
*/

// Constructor
EasySocket::EasySocket(int port, int addressFamily, int type, int protocol) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw new std::exception("WSAStartup has failed");

	hSocket = socket(addressFamily, type, protocol);

	if (hSocket == INVALID_SOCKET) {
		// Error occured
	}

	socketAddress = { 0 };
	socketAddress.sin_family = addressFamily;
	socketAddress.sin_port = htons(port);
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
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(host.c_str());

	// connect the socket
	if (connect(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		// Error
		return;
	}
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