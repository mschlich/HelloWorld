//
//  main.cpp
//  HelloWorld
//
//  Created by Marcus on 21/02/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include <iostream>
//#include <inet>


int main(int argc, const char * argv[]) {

    char *input = nullptr;
    input = new char[2];

    std::cout << "Your input:";
    std::cin  >> input;
    std::cout << "Your input was: " << input << "\n";
    
    delete input;
    return 0;
}
