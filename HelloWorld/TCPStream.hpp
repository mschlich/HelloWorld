//
//  TCPClientStream.hpp
//  HelloWorld
//
//  Created by Marcus on 02/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#ifndef TCPStream_hpp
#define TCPStream_hpp

#include <string>
#include <memory>

#include "Exceptions.hpp"

namespace org_xerobot {
    
    struct s_socket;
    
    // ********************************************************************************
    // Begin of class TCPStreamBase ***************************************************
    // ********************************************************************************
    class TCPStreamBase {
        
    protected:
        std::string _ipAdress;
        unsigned int _port;
        s_socket *_sockImpl;
        
    public:
        TCPStreamBase();
        TCPStreamBase(const std::string &address);
        TCPStreamBase(const std::string &address, unsigned int port);
        TCPStreamBase(const TCPStreamBase &toCopy);
        
        TCPStreamBase &operator=(const TCPStreamBase &toCopy);
        
        // Open the stream.
        virtual void open() throw (const NetException) = 0;
        
        // Close the stream.
        virtual void close() throw (const NetException) = 0;
        
    protected:
        virtual ~TCPStreamBase();
        
    };
    
    
    // ********************************************************************************
    // Begin of class TCPClientStream *************************************************
    // ********************************************************************************
    class TCPClientStream : public TCPStreamBase {
        
    public:
        TCPClientStream(const std::string &address);
        TCPClientStream(const std::string &address, unsigned int port = 80);
        
        // Returns true if the same socket (Family, Address, Port) is used.
        bool operator==(const TCPClientStream &toCompare) const;
        
        // Returns true if differen sockets are used.
        bool operator!=(const TCPClientStream &toCompare) const;
        
        // Receive something from ne twork
        const TCPClientStream &operator>>(std::string &toReceive) const throw (const NetException);
        
        // Send something into the network
        TCPClientStream &operator<<(const std::string &toSend) throw (const NetException);
        
        // Open the stream.
        void open() throw (const NetException) override;
        
        // Close the stream.
        void close() throw (const NetException) override;
    };
    
    // ********************************************************************************
    // Begin of class TCPServerWorker *************************************************
    // ********************************************************************************
    class TCPServerStreamWorker {
        
        // Do actual work. In case of error throw an exception.
        virtual void work() throw (const BaseException) = 0;
        
        inline virtual ~TCPServerStreamWorker() {};
        
    };
    
    // ********************************************************************************
    // Begin of class TCPServerStream *************************************************
    // ********************************************************************************
    class TCPServerStream {
        
    private:
        std::string _ipAddress;
        unsigned int _port;
        s_socket *_sockImpl;
        TCPServerStreamWorker *_worker;
        
    public:
        TCPServerStream();
        TCPServerStream(const std::string &address);
        TCPServerStream(TCPServerStreamWorker *worker,
                        const std::string &address = "localhost",
                        unsigned int port = 63000);
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
    };
    
};

#endif /* TCPStream_hpp */
