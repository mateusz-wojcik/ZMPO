#include "stdafx.h"
#include "CPunkt.h"

CPunkt::CPunkt(int x, int y) : x(new int(x)), y(new int(y)) 
{
}

CPunkt::CPunkt(CPunkt& other): x(new int(other.getX())), y(new int(other.getY()))
{
}

CPunkt::~CPunkt()
{
	delete x;
	delete y;
}

CPunkt& CPunkt::operator=(CPunkt& other)
{
	this->setX(other.getX());
	this->setY(other.getY());
	return *this;
}

int CPunkt::getX()
{
	return *x;
}

int CPunkt::getY()
{
	return *y;
}

void CPunkt::setX(int x)
{
	*this->x = x;
}

void CPunkt::setY(int y)
{
	*this->y = y;
}

std::ostream &operator << (std::ostream& output, CPunkt& point)
{
	output << "(" << point.getX() << "," << point.getY() << ")";
	return output;
}