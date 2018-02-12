#include "stdafx.h"
#include "CSparseCell.h"
#include <iostream>
#include <sstream>


CSparseCell::CSparseCell()
{
	std::cout << "CSparseCell" << std::endl;
}

CSparseCell::CSparseCell(int* coords, int coordsLength, int value)
{
	coordinates = new int[coordsLength];
	for (int i = 0; i < coordsLength; i++)
	{
		coordinates[i] = coords[i];
	}
	coordinatesLength = coordsLength;
	value = value;
}

CSparseCell::~CSparseCell()
{
}

void CSparseCell::operator=(CSparseCell &other)
{
	value = other.value;
	coordinatesLength = other.getCoordinatesLength();
	int *newCoordinates = new int[coordinatesLength];
	for (int i = 0; i < coordinatesLength; i++)
	{
		newCoordinates[i] = other.getCoordinates()[i];
	}
	delete coordinates;
	coordinates = newCoordinates;
}

int CSparseCell::getValue()
{
	return value;
}

int* CSparseCell::getCoordinates()
{
	return coordinates;
}

int CSparseCell::getCoordinatesLength()
{
	return coordinatesLength;
}

std::string CSparseCell::toString()
{
	std::stringstream ss;
	for (int i = 0; i < coordinatesLength; i++)
	{
		ss << coordinates[i] << ",";
	}
	return ss.str();
}
