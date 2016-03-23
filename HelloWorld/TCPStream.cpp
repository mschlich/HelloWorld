//
//  TCPStream.cpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include "TCPStream.hpp"
#include <sys/socket.h>
/*
class TCPStream {
    
private:
    int socket;
    unsigned int ipAdress;
    unsigned int port;
    
public:
    TCPStream();
    TCPStream(int Address);
    TCPStream(const TCPStream &toCopy);
    TCPStream &operator=(const TCPStream &toCopy);
    ~TCPStream();
    
};*/

TCPStream::TCPStream() : socket(0), ipAdress(0), port(0) {};

TCPStream::TCPStream(int Address) : socket(0), ipAdress(0), port(0) {
    this->socket = ::socket(PF_INET, SOCK_STREAM, 0);
    
}

TCPStream::~TCPStream() {
    if (this->socket > 0) {
        ::shutdown(this->socket, 2);
    }
}