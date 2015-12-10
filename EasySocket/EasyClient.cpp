#include "EasySocket.hpp"
using namespace easysock;

/** @file EasyClient.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Client wrapper implementation for the EasySocket library
*/

// Constructor
EasyClient::EasyClient(std::string host, int port, Type clientType) {
	this->easySocket = EasySocket(AF_INET, static_cast<int>(clientType), 0);
}

// Destructor
EasyClient::~EasyClient() {
	
}