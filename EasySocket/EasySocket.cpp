#include "EasySocket.hpp"
using namespace easysock;

/** @file EasySocket.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Wrapper implementation for the Socket library API
*/

// Default constructor - currently, having a member of EasySocket in EasyServer and EasyClient
// makes the compiler complain that we need a default constructor in EasySocket so when they
// are initialized, the members are too. This might suffice, not sure if it'll create copies
// that get destroyed immediately anyway though.
EasySocket::EasySocket() {
	EasySocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

// Constructor
EasySocket::EasySocket(const int addressFamily, const int type, const int protocol) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw std::exception("WSAStartup has failed");

	hSocket = socket(addressFamily, type, protocol);

	if (hSocket == INVALID_SOCKET) {
		throw std::exception("socket has failed");
	}

	socketAddress = { 0 };
	socketAddress.sin_family = addressFamily;
}

EasySocket::EasySocket(const SOCKET socket) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw std::exception("WSAStartup has failed");

	hSocket = socket;
}

// Destructor
EasySocket::~EasySocket() {
	cleanSocket();	
	cleanWSA(); 
}

void EasySocket::Connect(const std::string host, const int port) {
	// Create the server address
	socketAddress.sin_port = htons(port);
	inet_pton(AF_INET, host.c_str(), &socketAddress.sin_addr.s_addr);

	// connect the socket
	if (connect(hSocket, reinterpret_cast<SOCKADDR*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR) {
		throw std::exception("Connect has failed");
	}
}

std::vector<char> EasySocket::Receive(const int flags) const
{
	std::vector<char> buffer(1024);
	int numBytes = recv(hSocket, buffer.data(), buffer.size(), flags);
	if (numBytes == SOCKET_ERROR) {
		throw std::exception("Receive has failed");
	}
	buffer.resize(numBytes);
	return buffer;
}

void EasySocket::Listen(const int backlog) const
{
	if (listen(hSocket, backlog) == SOCKET_ERROR) {
		throw std::exception("Listen has failed");
	}
}

void EasySocket::Bind(const std::string host, const int port, const int address_family) const
{
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family = address_family;
	serverAddress.sin_port = htons(port);
	inet_pton(address_family, host.c_str(), &serverAddress.sin_addr.s_addr);

	if (bind(hSocket, reinterpret_cast<SOCKADDR*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		throw std::exception("Bind has failed");
	}
}

EasySocket EasySocket::Accept() const
{
	SOCKET hAccepted = SOCKET_ERROR;
	while (hAccepted == SOCKET_ERROR) {
		hAccepted = accept(hSocket, nullptr, nullptr);
	}
	return EasySocket(hAccepted);
}

// --------------------------------- //
//         Private Functions         //
// --------------------------------- //

void EasySocket::cleanSocket() const {
	closesocket(hSocket);	// Close socket handle
}

void EasySocket::cleanWSA() {
	WSACleanup();			// Clean up WSA information
}