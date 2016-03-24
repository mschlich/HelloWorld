//
//  BaseException.cpp
//  HelloWorld
//
//  Created by Marcus on 23/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include "Exceptions.hpp"

using namespace org_xerobot;

// ********************************************************************************
// Begin of class BaseException ***************************************************
// ********************************************************************************
const int BaseException::__initNumber = -1000;

BaseException::BaseException() : _errorNumber (BaseException::__initNumber),
    _errorMessagge("") {}

BaseException::BaseException(int errorNumber, std::string errorMessage) :
    _errorNumber(errorNumber), _errorMessagge(errorMessage){}


BaseException::BaseException(int errorNumber, const char *errorMessage) :
    _errorNumber(errorNumber), _errorMessagge(errorMessage) {}

bool BaseException::operator==(const BaseException &toCompare) const {
    return (_errorMessagge == toCompare._errorMessagge &&
            _errorNumber == toCompare._errorNumber);
}

bool BaseException::operator!=(const BaseException &toCompare) const {
    return (_errorMessagge != toCompare._errorMessagge ||
            _errorNumber != toCompare._errorNumber);
}

void BaseException::setErrorNumber(int errorNumber) {
    _errorNumber = errorNumber;
}

int BaseException::getErrorNumber() const {
    return _errorNumber;
}

void BaseException::setErrorMessage(const char *errorMessage) {
    _errorMessagge = errorMessage;
}

void BaseException::setErrorMessage(const std::string &errorMessage) {
    _errorMessagge = errorMessage;
}

const char *BaseException::getErrorMessage() const {
    return _errorMessagge.c_str();
}

std::string BaseException::getErrorMessageAsString() const {
    return _errorMessagge;
}

std::string BaseException::toString() const {
    std::string helper("ErrorMessage: " + _errorMessagge);
    helper += " (";
    helper +=  std::to_string(_errorNumber);
    helper += ")";
    return helper;
}

// *******************************************************************************
// Begin of class NetException ***************************************************
// *******************************************************************************
const std::string NetException::__msgPrefix("NET_EXCEPTION - ");

NetException::NetException(int errorNumber, std::string errorMessage) :
    BaseException(errorNumber, errorMessage) {}

NetException::NetException(int errorNumber, const char *errorMessage) :
    BaseException(errorNumber, errorMessage){}

std::string NetException::toString() const {
    return __msgPrefix + BaseException::toString();
}

