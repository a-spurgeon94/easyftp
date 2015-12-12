#if !defined (GUARD_EASYCLIENT_HPP)
#define GUARD_EASYCLIENT_HPP

/** @file EasyClient.hpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Client Application Class - Header
*/

#include <EasySocket.hpp>
using namespace std;
using namespace easysock;

// Encapsulates Client information related to sockets and interacting with a server
class EasyClient {
	// Data
private:
	EasySocket easySocket;
	ProtocolType type;
	string host;
	int port;

public:

	EasyClient() = delete;
	EasyClient(int port, ProtocolType type = ProtocolType::TCP);
	~EasyClient();
	
	void Connect(std::string host);
	
};
#endif