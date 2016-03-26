//
//  main.cpp
//  HelloWorld
//
//  Created by Marcus on 21/02/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include <iostream>
#include "TCPStream.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string googleIP("216.58.213.35");
    string spiegelIP("62.138.116.3");
    //string spiegelIP("62.138.116.3333");
    string loopBackIP("127.0.0.1");
    int httpPort = 80;

    org_xerobot::TCPClientStream stream(spiegelIP, httpPort);
    try {
        stream.open();
    } catch (org_xerobot::NetException &e) {
        cout << "Unable to establish connection." << endl;
        cout << e.toString() << endl;
        return -1;
    }
    cout << "Stream opnened successfully" << endl;
    
    try {
        stream << "GET http://www.spiegel.de HTTP/1.0\n" << "HOST:www.spiegel.de\n" <<  "\n\n";
    } catch (org_xerobot::NetException e) {
        cout << "Unable to sent data " << endl;
        cout << e.toString() << endl;
        return -1;
    }

    string reply;
    try {
         stream >> reply;
    } catch (org_xerobot::NetException e) {
        cout << "Unable to receive data " << endl;
        cout << e.toString() << endl;
        return -1;
    }
    cout << "Reply was: " << endl;
    cout << reply << endl;
    
    try {
        stream.close();
    } catch (org_xerobot::NetException e) {
        cout << "Error closing network stream." << endl;
        cout << e.toString() << endl;
        return -1;
    }
    cout << "Stream closed successfully" << endl;
    
    return 0;
}
