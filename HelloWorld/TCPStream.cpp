//
//  TCPClientStream.cpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include "TCPStream.hpp"

#include <cerrno>
#include <string>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace org_xerobot;

// ********************************************************************************
// Begin of struct s_socket *******************************************************
// ********************************************************************************
struct org_xerobot::s_socket {
    
    int _referenceCount;
    int _socket;
    
    struct addrinfo *_servInfo;
    
    s_socket() : _referenceCount(1), _socket(0), _servInfo(nullptr)  {}
    
    ~s_socket() {
        if (_servInfo != nullptr) freeaddrinfo(_servInfo);
    }
};

// ********************************************************************************
// Begin of class TCPStreamBase **++++*********************************************
// ********************************************************************************
TCPStreamBase::TCPStreamBase() : _ipAdress(""), _port(0), _sockImpl(new s_socket) {}

TCPStreamBase::TCPStreamBase(const std::string &address) :
_ipAdress(address), _port(0), _sockImpl(new s_socket) {}

TCPStreamBase::TCPStreamBase(const std::string &address, unsigned int port) :
_ipAdress(address), _port(port), _sockImpl(new s_socket) {}


TCPStreamBase::TCPStreamBase(const TCPStreamBase &toCopy) :
_ipAdress(toCopy._ipAdress), _port(toCopy._port), _sockImpl(toCopy._sockImpl) {
    ++_sockImpl->_referenceCount;
}

TCPStreamBase &TCPStreamBase::operator=(const TCPStreamBase &toCopy) {
    _ipAdress = toCopy._ipAdress;
    _port = toCopy._port;
    _sockImpl = toCopy._sockImpl;
    
    ++_sockImpl->_referenceCount;
    
    return *this;
}

TCPStreamBase::~TCPStreamBase() {
    --_sockImpl->_referenceCount;
    if (_sockImpl->_referenceCount <= 0) {
        shutdown(_sockImpl->_socket, 2);
        delete _sockImpl;
    }
}

// ********************************************************************************
// Begin of class TCPClientStream ++++*********************************************
// ********************************************************************************
TCPClientStream::TCPClientStream(const std::string &address)
: TCPStreamBase::TCPStreamBase(address) {}

TCPClientStream::TCPClientStream(const std::string &address, unsigned int port)
: TCPStreamBase::TCPStreamBase(address, port) {}

void TCPClientStream::open() throw (const NetException) {
    
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    
    hints.ai_family = AF_UNSPEC; // Address family: Unspecific
    hints.ai_socktype = SOCK_STREAM; // Stream Socket (i.e. TCP)
    hints.ai_flags = AI_PASSIVE; // Use local IP Address
    std::string port = std::to_string(_port);
    
    int status = getaddrinfo(_ipAdress.c_str(),
                             port.c_str(), &hints,
                             &_sockImpl->_servInfo);
    if (status) {
        if (_sockImpl->_servInfo != nullptr) freeaddrinfo(_sockImpl->_servInfo);
        throw (NetException(status, gai_strerror(status)));
    }
    
    if (_sockImpl->_servInfo == nullptr) {
        throw (NetException(65001, "Could not resolve address: " + _ipAdress));
    }
    
    // Open socket and throw exception in case of error
    _sockImpl->_socket = socket(_sockImpl->_servInfo->ai_family, SOCK_STREAM, 0);
    if (_sockImpl->_socket < 0) {
        freeaddrinfo(_sockImpl->_servInfo);
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

    /*
    sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = htons(_port);
    
    if (inet_aton(_ipAdress.c_str(), &name.sin_addr) == 0) {
        throw (NetException(650001, "IPv4 Address could not be converted by inet_aton()"));
    }*/
    
    
    if (connect(_sockImpl->_socket,
                _sockImpl->_servInfo->ai_addr,
                _sockImpl->_servInfo->ai_addrlen) <  0) {
        freeaddrinfo(_sockImpl->_servInfo);
        throw (NetException(errno, strerror(errno)));
    }
}

void TCPClientStream::close() throw (const NetException) {
    if (shutdown(_sockImpl->_socket, 1) < 0) {
        throw (NetException(errno, strerror(errno)));
    }
}

bool TCPClientStream::operator==(const TCPClientStream &toCompare) const {
    return ( _sockImpl == toCompare._sockImpl);
}


bool TCPClientStream::operator!=(const TCPClientStream &toCompare) const {
    return (_sockImpl != toCompare._sockImpl);
}

// Receive something from network
const TCPClientStream & TCPClientStream::operator>>(std::string &toReceive)const
throw (const NetException) {
    const int buffSize = 2048;
    char *buffer = new char[buffSize];
    memset(buffer, 0, buffSize);
    size_t bytesReceived = 0;

    while ((bytesReceived  = recv(_sockImpl->_socket, buffer, buffSize, 0)) > 0) {
        toReceive += buffer;
        memset(buffer, 0, buffSize);
    }
    
    delete[] buffer;
 
    return *this;
}

// Send something into the network
TCPClientStream &TCPClientStream::operator<<(const std::string &toSend)
throw (const NetException) {
    if (send(_sockImpl->_socket, toSend.c_str(), toSend.length(), 0) < 0) {
        throw (NetException(errno, strerror(errno)));
    };
    return *this;
}

// ********************************************************************************
// Begin of class TCPServerStream *************************************************
// ********************************************************************************
/*class TCPServerStream {
    
private:
    std::string _ipAddress;
    unsigned int _port;
    s_socket *_sockImpl;
    auto_ptr<TCPServerStreamWorker> _worker;
    
public:
    TCPServerStream(const TCPServerStream &toCopy);
    
    TCPServerStream &operator=(const TCPServerStream &toCopy);
    
    // Open the stream and start processing by accepting client requests and handling
    // them over to TCPServerStreamWorker::work().
    void open() throw (const NetException);
    
    // Closes the stream and stops processing. Any queued client requests will be
    // handled by the TCPServerStreamWorker..
    void close() throw (const NetException);
    
    // Closes the stream and stops processing. Any queued client requests will be
    // flushed.
    void terminate() throw (const NetException);
    
    ~TCPServerStream();
};*/

TCPServerStream::TCPServerStream() : _ipAddress(""), _port(0), _sockImpl(new s_socket),
    _worker(nullptr) {}

TCPServerStream::TCPServerStream(const std::string &address) : _ipAddress(address), _port(0),
    _sockImpl(new s_socket), _worker(nullptr) {}

TCPServerStream::TCPServerStream(TCPServerStreamWorker *worker,
                                 const std::string &address,
                                 unsigned int port) : _ipAddress(address), _port(port),
    _sockImpl(new s_socket), _worker(worker) {}

TCPServerStream::~TCPServerStream() {
    
}
