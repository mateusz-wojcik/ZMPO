#pragma once
#include <string>
#include "CSparseCell.h" //czy tak powinno byc?

#define defaultName "SparseMatrix";

const int defaultDefinedCellsLength = 5;

class CSparseMatrix
{
public:
	CSparseMatrix();
	CSparseMatrix(std::string name);
	CSparseMatrix(const CSparseMatrix &other);
	~CSparseMatrix();

	//void???
	void operator = (CSparseMatrix &other);

	//co prywatne a co publiczne?
	std::string getMatrixName() const;
	std::string matriceToString();
	std::string matToString(int dimension, int* coords);
	std::string matToString();
	CSparseCell getCell(int* coords);
	int getDefinedCellsLength();
	int getdefaultValue();
	int getRangesLength();
	CSparseCell** getDefinedCells();
	void setDefinedCellsLength(int length);
	void setDimensionsRanges(int* tmpRanges); //ustaw zakres dla wymiarow
	void setDimensionRange(int tmpRange, int off);
	void setCellValue(int *coords, int coordsLength, int value);
	void setRangesLength(int length);
	void rename(std::string newName);
	void deleteAll();
	bool isCoordsSame(int* coords, int coordsLength, int* coords2, int coords2Length);

private:
	void reallocateCells();
	void copyCells(CSparseMatrix &other);
	int findFreeIndex();

	CSparseCell **definedCells;
	int *dimensionsRanges; //tablica zakresow dla wymiarow
	int definedCellsLength, defaultValue, rangesLength; //rangeslen -> ilosc wymiarow
	std::string matrixName;
};

