//
// Created by Octavian Custura on 20/04/2020.
//

#include "Exceptions.h"

std::string RepositoryException::what() {
	return exception_name;
}

RepositoryException::RepositoryException(const std::string & exceptionString):exception_name(exceptionString) {}

ValidationException::ValidationException(const std::string &exception):exception_name(exception) {}

std::string ValidationException::what() {
	return exception_name;
}

