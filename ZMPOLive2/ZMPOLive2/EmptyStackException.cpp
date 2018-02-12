#include "stdafx.h"
#include "EmptyStackException.h"


EmptyStackException::EmptyStackException()
{
}


EmptyStackException::~EmptyStackException()
{
}


std::string EmptyStackException::getError()
{
	return ERROR;
}

int EmptyStackException::getErrorCode()
{
	return ERROR_CODE;
}