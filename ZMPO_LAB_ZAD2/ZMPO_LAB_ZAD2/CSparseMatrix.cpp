#include "stdafx.h"
#include "CSparseMatrix.h"
#include <string>
#include <iostream>
#include <sstream>


CSparseMatrix::CSparseMatrix()
{
	matrixName = defaultName;
	definedCellsLength = defaultDefinedCellsLength;
	definedCells = new CSparseCell*[definedCellsLength];
	std::cout << "create: " << matrixName << std::endl;
}

CSparseMatrix::CSparseMatrix(std::string name)
{
	matrixName = name;
	definedCellsLength = defaultDefinedCellsLength;
	definedCells = new CSparseCell*[definedCellsLength];
	std::cout << "create: " << matrixName << std::endl;
}

CSparseMatrix::CSparseMatrix(const CSparseMatrix &other)
{
    matrixName = other.matrixName + "_copy";
	defaultValue = other.defaultValue;
	setRangesLength(other.rangesLength);
	setDimensionsRanges(other.dimensionsRanges);
	definedCellsLength = defaultDefinedCellsLength;
	definedCells = new CSparseCell*[definedCellsLength];
	std::cout << "create: " << matrixName << std::endl;
}

CSparseMatrix::~CSparseMatrix()
{
	/*for (int i = 0; i < definedCellsLength; i++)
	{
		if(definedCells[i] != NULL) delete definedCells[i];
	}*/
	//delete definedCells;
	//deleteAll();
	std::cout << "destroy: " << matrixName << std::endl;
}

void CSparseMatrix:: operator = (CSparseMatrix &other)
{
	definedCellsLength = other.definedCellsLength;
	defaultValue = other.defaultValue;
	setRangesLength(other.rangesLength);
	//usunac tablice! delete
	setDimensionsRanges(other.dimensionsRanges);
	copyCells(other);
}

//metody ponizej
//publiczne

std::string CSparseMatrix::getMatrixName() const
{
	return matrixName;
}

std::string CSparseMatrix::matriceToString()
{
	std::stringstream result;
	result << getMatrixName() << " size: [";
	for (int i = 0; i < rangesLength; i++)
	{
		if (i == rangesLength - 1)
		{
			result << dimensionsRanges[i] << "]";
		}
		else
		{
			result << dimensionsRanges[i] << ",";
		}
	}
	return result.str();
}

int CSparseMatrix::getDefinedCellsLength()
{
	return definedCellsLength;
}

int CSparseMatrix::getdefaultValue()
{
	return defaultValue;
}

int CSparseMatrix::getRangesLength()
{
	return rangesLength;
}

CSparseCell** CSparseMatrix::getDefinedCells()
{
	return definedCells;
}

//tablica? ustawia ilosc wymiarow
void CSparseMatrix::setDefinedCellsLength(int dims)
{
	definedCellsLength = dims;
}

void CSparseMatrix::setDimensionsRanges(int* ranges)
{
	for (int i = 0; i < rangesLength; i++)
	{
		dimensionsRanges[i] = ranges[i]; //wartosc?
	}
}

void CSparseMatrix::setDimensionRange(int tmpRange, int off)
{
	dimensionsRanges[off] = tmpRange;
}

//czy ta metoda nie powinna byc w cell? i skoro jest zaprzyjazniona to po co seter?
void CSparseMatrix::setCellValue(int* coords, int coordsLength, int value)
{
	if (value != defaultValue)
	{
		int freeIndex = findFreeIndex();
		if (freeIndex != -1)
		{
			CSparseCell newCell; //da sie na pewno lepiej
			*(definedCells[freeIndex]) = newCell;
			newCell.coordinatesLength = coordsLength;
			for (int i = 0; i < coordsLength; i++)
			{//czy to jest dobre kopiowanie? chyba nie
				newCell.coordinates[i] = coords[i];
			}
		}
	}
}

void CSparseMatrix::setRangesLength(int length)
{
	dimensionsRanges = new int[length];
	rangesLength = length;
}

void CSparseMatrix::rename(std::string newName)
{
	matrixName = newName;
}

void CSparseMatrix::deleteAll()
{
	delete definedCells;
	delete dimensionsRanges;
}

//prywatne

void CSparseMatrix::reallocateCells() //czy dobrze?
{
	CSparseCell **newDefinedCells = new CSparseCell*[definedCellsLength * 2];
	for (int i = 0; i < definedCellsLength; i++)
	{
		*(newDefinedCells[i]) = *(definedCells[i]);
	}
	delete definedCells;
	definedCells = newDefinedCells;
	definedCellsLength *= 2;
}

void CSparseMatrix::copyCells(CSparseMatrix &other)
{
	int otherLength = other.getDefinedCellsLength();
	CSparseCell **newDefinedCells = new CSparseCell*[otherLength];
	
	for (int i = 0; i < otherLength; i++)
	{ //nalezy przeciazyc tutaj operator =   oraz skopiowac zakresy dla wymiarow
		//if(newDefinedCells[i] != NULL) *(newDefinedCells[i]) = *((other.getDefinedCells()[i])); //??
		//newDefinedCells[i] = new CSparseCell(other.getDefinedCells()[i]->coordinates, other.getDefinedCells()[i]->coordinatesLength, other.getDefinedCells()[i]->value);
	}
	/*for (int i = 0; i < definedCellsLength; i++)
	{
		if(definedCells[i] != NULL) delete definedCells[i];
	}*/
	delete definedCells;
	definedCells = newDefinedCells;
	definedCellsLength = otherLength;
}

int CSparseMatrix::findFreeIndex()
{
	for (int i = 0; i < definedCellsLength; i++)
	{//?????????
		if (definedCells[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}

/*std::string CSparseMatrix::printAll()
{
	std::stringstream ss;
	for (int i = 0; i < rangesLength; i++)
	{
		for (int j = 0; j < dimensionsRanges[i]; j++)
		{
			ss << "[";;
			for (int k = 0; k < rangesLength; k++)
			{
				if(k == i) ss << k;
				else ss << k << ",";
			}
			ss << "]:" << ";";
		}
	}

	return ss.str();
}*/

CSparseCell CSparseMatrix::getCell(int* coords)
{
	for (int i = 0; i < definedCellsLength; i++)
	{
		if (isCoordsSame(coords, rangesLength, definedCells[i]->coordinates, definedCells[i]->coordinatesLength)) return *definedCells[i];
	}
}

bool CSparseMatrix::isCoordsSame(int* coords, int coordsLength, int* coords2, int coords2Length)
{
	if (coordsLength != coords2Length)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < coordsLength; i++)
		{
			if (coords[i] != coords2[i]) return false;
		}
	}
	return true;
}

std::string CSparseMatrix::matToString() {
	int* array = new int[0];
	std::string s = matToString(0, array);
	delete[] array;
	return s;
}

std::string CSparseMatrix::matToString(int dimension, int* coords) { //dimension jest zawsze równe iloœci elementów w tablicy coords.
	if (dimension == rangesLength) { //dimension == iloœci wymiarów, zatem 'coords' wskazuje na konkretne koordynaty.
		return getCell(coords).toString();
	}
	else {
		std::stringstream ss;
		for (int j = 0; j < dimensionsRanges[dimension]; j++) {
			/* np. je¿eli trzeci wymiar ma wielkoœæ 5, to dla dimension=3 zostanie wykonane 5 razy,
			za ka¿dym razem otrzymuj¹c kolejn¹ liczbê pod zmienn¹ 'j' 
			//skopiowanie tablicy koordynatów z dodatkowym elementem*/
			int* newCoords = new int[dimension + 1];
			for (int i = 0; i < dimension; i++) {
				newCoords[i] = coords[i];
			}
			//wprowadzenie 'j' na koñcu tablicy
			newCoords[dimension] = j;
			ss << matToString(dimension + 1, newCoords);
			delete[] newCoords;
		}
		return ss.str();
	}
}