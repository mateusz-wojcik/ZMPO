#include "stdafx.h"
#include "FullStackException.h"


FullStackException::FullStackException()
{
}


FullStackException::~FullStackException()
{
}

std::string FullStackException::getError()
{
	return ERROR;
}

int FullStackException::getErrorCode()
{
	return ERROR_CODE;
}