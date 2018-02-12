#include "stdafx.h"
#include "CProstokat.h"
#include <algorithm>

CProstokat::CProstokat(CPunkt& p1, CPunkt& p2) : leftBottom(std::min(p1.getX(), p2.getX()), std::min(p1.getY(), p2.getY()))
{
	this->width = abs(p2.getX() - p1.getX());
	this->height = abs(p2.getY() - p1.getY());
}

CProstokat::CProstokat(int x1, int y1, int x2, int y2) : leftBottom(std::min(x1,x2), std::min(y1,y2))
{
	this->width = abs(x2 - x1);
	this->height = abs(y2 - y1);
}

CProstokat::~CProstokat()
{
}

CProstokat CProstokat::operator+(CProstokat& other)
{
	int leftX = std::min(leftBottom.getX(), other.leftBottom.getX());
	int leftY = std::min(leftBottom.getY(), other.leftBottom.getY());
	int rightX = std::max(leftBottom.getX() + width, other.leftBottom.getX() + other.width);
	int rightY = std::max(leftBottom.getY() + height, other.leftBottom.getY() + other.height);

	return CProstokat(leftX, leftY, rightX, rightY);
}

std::ostream &operator << (std::ostream& output, CProstokat& pr)
{
	output << "Punkt 1:" << pr.leftBottom << " Punkt 2: (" << pr.leftBottom.getX() + pr.width << "," << pr.leftBottom.getY() + pr.height << ")\n";
	return output;
}

