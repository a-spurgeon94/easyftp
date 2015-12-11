/** @file EasyClient.cpp
*   @author Anthony Spurgeon, Ryan Speets
*   @date 08-12-2015
*   @brief Client Application Class - Implementation
*/

#include "EasyClient.hpp"

// Constructor
EasyClient::EasyClient(int port, ProtocolType type) {
	this->port = port;
	this->type = type;
	this->easySocket = EasySocket(AF_INET, type, 0);
}

// Destructor
EasyClient::~EasyClient() {

}



void EasyClient::Connect(std::string host) {
	easySocket.Connect(host, port);
}