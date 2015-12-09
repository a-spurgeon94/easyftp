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

// --------------------------------- //
//         Private Functions         //
// --------------------------------- //

void EasySocket::cleanSocket() {
	closesocket(hSocket);	// Close socket handle
}

void EasySocket::cleanWSA() {
	WSACleanup();			// Clean up WSA information
}