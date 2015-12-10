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
}

EasySocket::EasySocket(SOCKET socket) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw new std::exception("WSAStartup has failed");

	hSocket = socket;
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
	int err = WSAGetLastError();
	int numBytes = recv(hSocket, buffer.data(), buffer.size(), flags);
	if (numBytes == SOCKET_ERROR) {
		err = WSAGetLastError();
		throw new std::exception("Receive has failed");
	}
	buffer.resize(numBytes);
	return buffer;
}

void EasySocket::Listen(int backlog) {
	if (listen(hSocket, backlog) == SOCKET_ERROR) {
		throw new std::exception("Listen has failed");
	}
}

void EasySocket::Bind(std::string host, int port, int address_family) {
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family = address_family;
	serverAddress.sin_port = htons(port);
	inet_pton(address_family, host.c_str(), &serverAddress.sin_addr.s_addr);

	if (bind(hSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		int x = WSAGetLastError();
		throw new std::exception("Bind has failed");
	}
}

EasySocket EasySocket::Accept() {
	SOCKET hAccepted = SOCKET_ERROR;
	while (hAccepted == SOCKET_ERROR) {
		hAccepted = accept(hSocket, NULL, NULL);
	}
	return EasySocket(hAccepted);
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