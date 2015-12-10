#if !defined (GUARD_EASYSOCKET_H)
#define GUARD_EASYSOCKET_H

#if defined (_DEBUG)
#pragma comment (lib, "easysocket-debug.lib")
#elif !defined (_DEBUG)
#pragma comment (lib, "easysocket.lib")
#endif


/** @file EasySocket.h
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Wrapper header for the Socket library API
*/

#include <string>
#include <exception>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

class EasySocket {
	// Data
private:
	SOCKET hSocket;
	WSAData wsaData;
	sockaddr_in socketAddress;

	void cleanSocket();
	void cleanWSA();
public:

	EasySocket(int addressFamily, int type, int protocol = 0);
	~EasySocket();

	void Connect(std::string host, int port);

	template <typename T>
	int Send(T buffer, int flags = 0);

	std::vector<char> Receive(int flags = 0);
};

// Had to move this to header because of templates.
template <typename T>
int EasySocket::Send(T buffer, int flags) {
	return send(hSocket, buffer.data(), buffer.size(), flags);
}

#endif