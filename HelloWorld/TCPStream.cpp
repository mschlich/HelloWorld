//
//  TCPStream.cpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include "TCPStream.hpp"

#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>

using namespace org_xerobot;

// ********************************************************************************
// Begin of struct s_socket *******************************************************
// ********************************************************************************
struct org_xerobot::s_socket {
    
    int _referenceCount;
    int _socket;
    
    s_socket() : _referenceCount(1), _socket(0) {}
    
    ~s_socket() {}
};


// ********************************************************************************
// Begin of class TCPStream ++++***************************************************
// ********************************************************************************
TCPStream::TCPStream() : _ipAdress(""), _port(0), _sockImpl(new s_socket) {}

TCPStream::TCPStream(std::string address) :
    _ipAdress(address), _port(0), _sockImpl(new s_socket) {}

TCPStream::TCPStream(std::string address, unsigned int port) :
    _ipAdress(address), _port(port), _sockImpl(new s_socket) {}

TCPStream::TCPStream(const TCPStream &toCopy) :
   _ipAdress(toCopy._ipAdress), _port(toCopy._port), _sockImpl(toCopy._sockImpl) {
   ++_sockImpl->_referenceCount;
}

TCPStream &TCPStream::operator=(const TCPStream &toCopy) {
    _ipAdress = toCopy._ipAdress;
    _port = toCopy._port;
    _sockImpl = toCopy._sockImpl;
    
    ++_sockImpl->_referenceCount;
    
    return *this;
}

void TCPStream::open() throw (const NetException) {
    
    // Open socket and throw exception in case of error
    _sockImpl->_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (_sockImpl->_socket < 0) {
        throw (NetException(errno, ::strerror(errno)));
    }
    
    // Create name struct and bind to socket
    /*struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = _port;
    name.sin_addr.s_addr =  inet_addr(_ipAdress.c_str());
    if (bind(_sockImpl->_socket, (sockaddr *) &name, sizeof(name)) <  0) {
        throw (NetException(errno, strerror(errno)));
    }*/
    
    // Connect to server
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = htons(_port);
    
    if (inet_aton(_ipAdress.c_str(), &name.sin_addr) == 0) {
        throw (NetException(650001, "IPv4 Address could not be converted by inet_aton()"));
    }
    
    
    if (connect(_sockImpl->_socket, (sockaddr *) &name, sizeof(name)) <  0) {
        throw (NetException(errno, strerror(errno)));
    }
}

void TCPStream::close() throw (const NetException) {
    if (shutdown(_sockImpl->_socket, 1) < 0) {
        throw (NetException(errno, strerror(errno)));
    }
}

bool TCPStream::operator==(const TCPStream &toCompare) const {
    return ( _sockImpl == toCompare._sockImpl);
}


bool TCPStream::operator!=(const TCPStream &toCompare) const {
    return (_sockImpl != toCompare._sockImpl);
}

// Receive something from network
const TCPStream & TCPStream::operator>>(std::string &toReceive) const throw (const NetException) {
    const int buffSize = 2048;
    char *buffer = new char[buffSize];
    memset(buffer, 0, buffSize);
    size_t bytesReceived = 0;

    while ((bytesReceived  = recv(_sockImpl->_socket, buffer, buffSize, 0)) > 0) {
        toReceive += buffer;
        memset(buffer, 0, buffSize);
    }
 
    return *this;
}

// Send something into the network
TCPStream &TCPStream::operator<<(const std::string &toSend) throw (const NetException) {
    if (send(_sockImpl->_socket, toSend.c_str(), toSend.length(), 0) < 0) {
        throw (NetException(errno, strerror(errno)));
    };
    return *this;
}


TCPStream::~TCPStream() {
    --_sockImpl->_referenceCount;
    if (_sockImpl->_referenceCount <= 0) {
        shutdown(_sockImpl->_socket, 2);
        delete _sockImpl;
    }
}