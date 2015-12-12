#include "EasySocket.hpp"
using namespace easysock;

/** @file EasySocket.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Wrapper for the Win32 Socket Library API - Implementation
*/

// --------------------------------- //
//            Constructors           //
// --------------------------------- //

// Default constructor - currently, having a member of EasySocket in EasyServer and EasyClient
// makes the compiler complain that we need a default constructor in EasySocket so when they
// are initialized, the members are too. This might suffice, not sure if it'll create copies
// that get destroyed immediately anyway though.


// Constructor
EasySocket::EasySocket(const int addressFamily, const ProtocolType type, const int protocol) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw EasySocketException(WSAGetLastError());

	hSocket = socket(addressFamily, static_cast<int>(type), protocol);

	if (hSocket == INVALID_SOCKET) {
		throw EasySocketException(WSAGetLastError());
	}

	socketAddress = { 0 };
	socketAddress.sin_family = addressFamily;
}


EasySocket::EasySocket(SOCKET socket, sockaddr_in addr) {
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
		throw EasySocketException(WSAGetLastError());
	socketAddress = addr;
	hSocket = socket;
}

std::string EasySocket::IpAddress() {
	char hostname[NI_MAXHOST];
	getnameinfo((sockaddr*) &socketAddress,
				sizeof(socketAddress),
				hostname,
				NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
	return std::string(hostname);
}

// Destructor
EasySocket::~EasySocket() {
	cleanSocket();	
	cleanWSA(); 
}


// --------------------------------- //
//           Functionality           //
// --------------------------------- //


void EasySocket::Connect(const std::string host, const int port) {
	// Create the server address
	socketAddress.sin_port = htons(port);
	inet_pton(AF_INET, host.c_str(), &socketAddress.sin_addr.s_addr);

	// connect the socket
	if (connect(hSocket, reinterpret_cast<SOCKADDR*>(&socketAddress), sizeof(socketAddress)) == SOCKET_ERROR) {
		throw EasySocketException(WSAGetLastError());
	}
}


int EasySocket::SendBuffer(const char *buffer, const int size, const int flags)
{
	int bytesSent = send(hSocket, buffer, size, flags);
	if (bytesSent != SOCKET_ERROR) {
		return bytesSent;
	}
	else
	{
		throw EasySocketException(WSAGetLastError());
	}
}

std::vector<char> EasySocket::Receive(const int size, const int flags)
{
	std::vector<char> buffer(size);
	int numBytes = recv(hSocket, buffer.data(), (int) buffer.size(), flags);
	if (numBytes == SOCKET_ERROR) {
		throw EasySocketException(WSAGetLastError());
	}
	buffer.resize(numBytes);
	return buffer;
}


void EasySocket::Listen(const int backlog)
{
	if (listen(hSocket, backlog) == SOCKET_ERROR) {
		throw EasySocketException(WSAGetLastError());
	}
}


void EasySocket::Bind(const std::string host, const int port)
{
	sockaddr_in serverAddress = { 0 };
	serverAddress.sin_family = socketAddress.sin_family;
	serverAddress.sin_port = htons(port);
	inet_pton(serverAddress.sin_family, host.c_str(), &serverAddress.sin_addr.s_addr);

	if (bind(hSocket, reinterpret_cast<SOCKADDR*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		throw EasySocketException(WSAGetLastError());
	}
}

std::string easysock::EasySocket::ReadString()
{
	// Get the string length
	int size = htonl(reinterpret_cast<int&>(*Receive(4).data()));
	// read it from the socket
	std::vector<char> data;
	while (data.size() < size) {
		std::vector<char> dataVec = Receive(size - static_cast<int>(data.size()));
		data.insert(data.end(), dataVec.begin(), dataVec.end());
	}
	return std::string(data.data(), size);
}

void easysock::EasySocket::WriteString(std::string string)
{
	// prepend the string with the length
	Send(htonl(static_cast<int>(string.size())));
	// send the string data
	SendBuffer(string.data(), static_cast<int>(string.size()));
}


EasySocket EasySocket::Accept()
{
	SOCKET hAccepted = SOCKET_ERROR;
	sockaddr_in addr;
	int addrSize = sizeof addr;
	hAccepted = accept(hSocket, (struct sockaddr *) &addr, &addrSize);
	if (hAccepted != SOCKET_ERROR) {
		return EasySocket(hAccepted, addr);
	}
	else
	{
		throw EasySocketException(WSAGetLastError());
	}
}


// --------------------------------- //
//         Private Functions         //
// --------------------------------- //

// Closes the socket
void EasySocket::cleanSocket() {
	closesocket(hSocket);	// Close socket handle
}

// Performs cleanup of WSA
void EasySocket::cleanWSA() {
	WSACleanup();			// Clean up WSA information
}