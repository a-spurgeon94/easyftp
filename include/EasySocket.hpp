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


namespace easysock {
	enum class Type { TCP = 1, UDP = 2 };


	// Encapsulates Socket library information and handles low-level interactions
	class EasySocket {
		// Data
	private:
		SOCKET hSocket;
		WSAData wsaData;
		sockaddr_in socketAddress;

		void cleanSocket() const;
		static void cleanWSA();
		EasySocket(SOCKET);
	public:

		EasySocket();
		EasySocket(const int addressFamily, const int type, const int protocol = 0);
		~EasySocket();

		template <typename T>
		int Send(const T buffer, const int flags = 0);
		std::vector<char> Receive(const int flags = 0) const;

		void Connect(const std::string host, const int port);
		void Listen(const int backlog = SOMAXCONN) const;
		void Bind(const std::string host, const int port, const int af = 0) const;

		EasySocket Accept() const;
	};


	// Encapsulates Server information related to sockets and responding to clients
	class EasyServer {
		// Data
	private:
		EasySocket easySocket;
		std::string host;
		int port;

	public:

		EasyServer() = delete;
		EasyServer(std::string host, int port, Type type);
		~EasyServer();
	};


	// Encapsulates Client information related to sockets and interacting with a server
	class EasyClient {
		// Data
	private:
		EasySocket easySocket;

	public:

		EasyClient() = delete;
		EasyClient(std::string host, int port, Type type);
		~EasyClient();
	};

	// Had to move this to header because of templates.
	template <typename T>
	int EasySocket::Send(const T buffer, const int flags) {
		return send(hSocket, buffer.data(), buffer.size(), flags);
	}
}
#endif