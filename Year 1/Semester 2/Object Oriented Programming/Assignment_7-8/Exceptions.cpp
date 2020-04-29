//
// Created by Octavian Custura on 20/04/2020.
//

#include "Exceptions.h"

const char* RepositoryException::what() {
	return exception_name.c_str();
}

RepositoryException::RepositoryException(const std::string & exceptionString):exception_name(exceptionString) {}

ValidationException::ValidationException(const std::string &exception):exception_name(exception) {}

const char* ValidationException::what() {
	return exception_name.c_str();
}

