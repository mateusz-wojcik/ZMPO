#pragma once
#include <string>
#define ERROR "Exception: Stack is empty!"
#define ERROR_CODE -2

class EmptyStackException
{
public:
	EmptyStackException();
	~EmptyStackException();

	std::string getError();
	int getErrorCode();
};

