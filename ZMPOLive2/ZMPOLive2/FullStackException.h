#pragma once
#include <string>
#define ERROR "Exception: Stack is Full!"
#define ERROR_CODE -1

class FullStackException
{
public:
	FullStackException();
	~FullStackException();

	std::string getError();
	int getErrorCode();
};

