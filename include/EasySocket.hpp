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
#include <sstream>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


namespace easysock {

	// Predefined Protocols
	enum class ProtocolType { TCP = SOCK_STREAM, UDP = SOCK_DGRAM };


	// Encapsulates excpetions encountered when interacting with the Win32 Socket Library API
	class EasySocketException : public std::exception {
	private:
		std::string msg;

	public:
		int errorCode;

		EasySocketException(const int& errorCode) {
			this->errorCode = errorCode;
			std::stringstream ss;

			// Get error description
			CHAR buffer[1024];
			FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, errorCode, 0, buffer, sizeof buffer, nullptr);

			ss << "Winsock Error #" << errorCode << ": " << buffer;
			msg = ss.str();
		}

		virtual const char* what() const throw() {
			return msg.c_str();
		}
	};


	// Encapsulates Win32 Socket Library information and handles startup, interactions, and cleanup
	class EasySocket {
	private:
		EasySocket(SOCKET socket, sockaddr_in addr);

		SOCKET hSocket;
		WSAData wsaData;
		sockaddr_in socketAddress;

		void cleanSocket();
		static void cleanWSA();

	public:

		EasySocket() : hSocket(INVALID_SOCKET) {}
		EasySocket(const int addressFamily, const ProtocolType type, const int protocol = 0);
		~EasySocket();

		template <typename T>
		int Send(const T buffer, const int flags = 0);
		int SendBuffer(const char *buffer, const int size, const int flags = 0);
		std::vector<char> Receive(const int flags = 0);

		void Connect(const std::string host, const int port);
		void Listen(const int backlog = SOMAXCONN);
		void Bind(const std::string host, const int port);

		std::string IpAddress();

		EasySocket Accept();
	};


	// Had to move this to header because of templates.
	template <typename T>
	int EasySocket::Send(const T buffer, const int flags) {
		int bytesSent = send(hSocket, (char *)&buffer, sizeof(buffer), flags);
		if (bytesSent != SOCKET_ERROR) {
			return bytesSent;
		}
		else {
			throw EasySocketException(WSAGetLastError());
		}
	}
}
#endif