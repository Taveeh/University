//
// Created by Octavian Custura on 20/04/2020.
//

#ifndef ASSIGNMENT_7_8_EXCEPTIONS_H
#define ASSIGNMENT_7_8_EXCEPTIONS_H
#include <exception>
#include <string>
class Exception: public std::exception {
public:
	virtual const char* what() = 0;
};

class RepositoryException: Exception {
private:
	const std::string& exception_name;
public:
	explicit RepositoryException(const std::string&);

	const char* what() override;
};

class ValidationException: Exception {
	const std::string& exception_name;
public:
	explicit ValidationException(const std::string& exception);

	const char* what() override;
};
#endif //ASSIGNMENT_7_8_EXCEPTIONS_H
