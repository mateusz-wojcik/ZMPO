#pragma once
#include <string>

class CSparseCell
{
public:
	friend class CSparseMatrix;
	CSparseCell();
	CSparseCell(int *coords, int coordsLength, int value);
	~CSparseCell();

	void operator = (CSparseCell &other);

	int getValue();
	int *getCoordinates();
	int getCoordinatesLength(); //czy getery potrzebne, gdy friend matrix?

private:
	std::string toString();
	int *coordinates;
	int value, coordinatesLength;
};

