//
//  TCPStream.hpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#ifndef TCPStream_hpp
#define TCPStream_hpp

#include <stdio.h>

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
    
};

#endif /* TCPStream_hpp */
