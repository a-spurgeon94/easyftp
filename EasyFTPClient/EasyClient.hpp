#if !defined (GUARD_EASYCLIENT_HPP)
#define GUARD_EASYCLIENT_HPP

/** @file EasyClient.hpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Client Application Class - Header
*/

#include <EasySocket.hpp>
using namespace easysock;

// Encapsulates Client information related to sockets and interacting with a server
class EasyClient {
	// Data
private:
	EasySocket easySocket;
	std::string host;
	int port;
	Type type;

public:

	EasyClient() = delete;
	EasyClient(std::string host, int port, Type type);
	~EasyClient();
};
#endif