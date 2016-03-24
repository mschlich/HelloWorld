//
//  TCPStream.hpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#ifndef TCPStream_hpp
#define TCPStream_hpp

#include <string>

#include "Exceptions.hpp"

namespace org_xerobot {
    
    struct s_socket;

    class TCPStream {
        
    private:
        std::string _ipAdress;
        unsigned int _port;
        s_socket *_sockImpl;
        
    public:
        TCPStream();
        TCPStream(std::string address);
        TCPStream(std::string address, unsigned int port);
        TCPStream(const TCPStream &toCopy);
        
        TCPStream &operator=(const TCPStream &toCopy);
        
        // Returns true if the same socket (Family, Address, Port) is used.
        bool operator==(const TCPStream &toCompare) const;
        
        // Returns true if differen sockets are used.
        bool operator!=(const TCPStream &toCompare) const;
        
        // Receive something from ne twork
        const TCPStream &operator>>(std::string &toReceive) const throw (const NetException);
        
        // Send something into the network
        TCPStream &operator<<(const std::string &toSend) throw (const NetException);
        
        // Open the stream.
        void open() throw (const NetException);
        
        // Close the stream.
        void close() throw (const NetException);
        
        ~TCPStream();
    };
    
};

#endif /* TCPStream_hpp */
