#pragma once

#include <exception>

class MessageException : public std::exception {

public:
	MessageException(char* message) : m_message(message) {};

private:
	char * m_message;

};