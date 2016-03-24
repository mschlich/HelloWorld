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

namespace org_xerobot {

    // ********************************************************************************
    // Begin of class BaseException ***************************************************
    // ********************************************************************************
    class BaseException {
        
    private:
        int _errorNumber;
        std::string _errorMessagge;
        
    public:
        
        BaseException();
        BaseException(int errorNumber, std::string errorMesage = "");
        BaseException(int errorNumber, const char *errorMessage);
        
        // Returns true if both errorNumber and errorMessage are equal.*/
        virtual bool operator==(const BaseException &toCompare) const;
        
        // Returns true if either errorNumber or errorMessage are not equal.*/
        virtual bool operator!=(const BaseException &toCompare) const;
        
        virtual void setErrorNumber(int errorNumber);
        virtual int getErrorNumber() const;
        
        virtual void setErrorMessage(const char *errorMessage);
        virtual void setErrorMessage(const std::string &errorMessage);
        virtual const char *getErrorMessage() const;
        virtual std::string getErrorMessageAsString() const;
        
        // Returns the Object's represenation as a string.
        virtual std::string toString() const;
        
    private:
        static const int __initNumber;
        
    };
    
    // ********************************************************************************
    // Begin of class NetException ****************************************************
    // ********************************************************************************
    class NetException : BaseException {
        
    private:
        static const std::string __msgPrefix;

    public:
        NetException(int errorNumber, std::string errorMesage = "");
        NetException(int errorNumber, const char *errorMessage);
        
        // Returns objects representation as string.
        virtual std::string toString() const;        
    };
    
};
    

#endif /* BaseException_hpp */
