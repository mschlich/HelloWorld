//
//  BaseException.cpp
//  HelloWorld
//
//  Created by Marcus on 23/03/16.
//  Copyright © 2016 marcus@xerbot.org. All rights reserved.
//

#include "ErrorHandling.hpp"

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
    std::string helper("ErrorMessage: ");
    helper += " (";
    helper += _errorNumber;
    helper += ")";
    return helper;
}