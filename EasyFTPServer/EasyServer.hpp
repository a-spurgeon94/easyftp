#if !defined (GUARD_EASYSERVER_HPP)
#define GUARD_EASYSERVER_HPP

/** @file EasyServer.hpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Server Application Class - Header
*/

#include <EasySocket.hpp>
using namespace std;
using namespace easysock;

// Encapsulates Server information related to sockets and responding to clients
class EasyServer {
	// Data
private:
	EasySocket easySocket;
	ProtocolType type;
	string host;
	int port;

public:

	EasyServer() = delete;
	EasyServer(int port, ProtocolType type = ProtocolType::TCP);
	~EasyServer();
};
#endif