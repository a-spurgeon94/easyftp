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
*   @brief Wrapper for the Win32 Socket Library API - Header
*/

#include <string>
#include <exception>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


namespace easysock {
	enum class Type { TCP = 1, UDP = 2 };


	// Encapsulates Win32 Socket Library information and handles startup, interactions, and cleanup
	class EasySocket {
		// Data
	private:
		SOCKET hSocket;
		WSAData wsaData;
		sockaddr_in socketAddress;

		void cleanSocket();
		static void cleanWSA();
		EasySocket(SOCKET socket, sockaddr_in addr);

	public:

		EasySocket();
		EasySocket(const int addressFamily, const int type, const int protocol = 0);
		~EasySocket();

		template <typename T>
		int Send(const T buffer, const int flags = 0);
		std::vector<char> Receive(const int flags = 0);

		void Connect(const std::string host, const int port);
		void Listen(const int backlog = SOMAXCONN);
		void Bind(const std::string host, const int port);

		EasySocket Accept();
	};


	// Had to move this to header because of templates.
	template <typename T>
	int EasySocket::Send(const T buffer, const int flags) {
		return send(hSocket, buffer.data(), (int) buffer.size(), flags);
	}
}
#endif