#include "EasySocket.hpp"
using namespace easysock;

/** @file EasyServer.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Server wrapper implementation for the EasySocket library
*/

// Constructor
EasyServer::EasyServer(std::string host, int port, Type serverType) {
	this->host = host;
	this->port = port;		
	this->easySocket = EasySocket(AF_INET, static_cast<int>(serverType), 0);
}

// Destructor
EasyServer::~EasyServer() {

}