//
//  BaseException.hpp
//  HelloWorld
//
//  Created by Marcus on 23/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#ifndef ErrorHandling_hpp
#define ErrorHandling_hpp

#include <string>

/**Base Exception is the base classe from which to derive all Exceptions.*/
class BaseException {
    
private:
    int _errorNumber;
    std::string _errorMessagge;
    
public:

    BaseException();
    BaseException(int errorNumber, std::string errorMesage = "");
    BaseException(int errorNumber, const char *errorMessage);
    
    // Returns true if both errorNumber and errorMessage are equal.*/
    virtual bool operator==(const BaseException &toCompare);
    
    // Returns true if either errorNumber or errorMessage are not equal.*/
    virtual bool operator!=(const BaseException &toCompare);

    virtual void setErrorNumber(int errorNumber);
    virtual int getErrorNumber();

    virtual void setErrorMessage(const char *errorMessage);
    virtual void setErrorMessage(const std::string &errorMessage);
    virtual const char *getErrorMessage();
    virtual const std::string &getErrorMessageAsString();
    
    // Returns the Object's represenation as a string.
    virtual const std::string &toString();
    
};

#endif /* BaseException_hpp */
