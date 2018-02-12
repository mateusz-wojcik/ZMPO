#include "stdafx.h"
#include "CSparseCell.h"
#include "CSparseMatrix.h"
#include <iostream>
#include <vector>

const int startVectorLen = 5;

using namespace std;

int main()
{
	vector<CSparseMatrix> vec;
	
	while (true)
	{
		string s;
		cin >> s;
		if (s == "addmat") //dziala
		{
			int dimNum, def;
			string name;
			cin >> dimNum;
			int *dimensions = new int[dimNum];
			for (int i = 0; i < dimNum; i++)
			{
				int tmp;
				cin >> tmp;
				dimensions[i] = tmp;
			}
			cin >> def;
			if (getchar() != '\r')
			{
				cin >> name;
				CSparseMatrix matrix(name);
				matrix.setRangesLength(dimNum);
				matrix.setDimensionsRanges(dimensions);
				vec.push_back(matrix);
			}
			else
			{
				CSparseMatrix matrix;
				matrix.setRangesLength(dimNum);
				matrix.setDimensionsRanges(dimensions);
				vec.push_back(matrix);
			}
		}
		else if (s == "list") //dziala
		{
			for (int i = 0; i < vec.size(); i++)
			{
				cout << "[" << i << "] - " << vec.at(i).matriceToString() << endl;
			}
		}
		else if (s == "del")
		{
			int matoff;
			cin >> matoff;
			//usuwanie
		}
		else if (s == "delall")
		{
			
		}
		else if (s == "def") //ma szanse dzia³ac
		{
			int matoff, val, len;
			cin >> matoff;
			len = vec.at(matoff).getRangesLength();
			int *tmpcoordinates = new int[len];
			for (int i = 0; i < len; i++)
			{
				int tmp;
				cin >> tmp;
				tmpcoordinates[i] = tmp;
			}
			cin >> val;
			vec.at(matoff).setCellValue(tmpcoordinates, len, val);
		}
		else if (s == "print")
		{
			int matoff;
			cin >> matoff;
			cout << vec.at(matoff).matToString() << endl;;
		}
		else if (s == "clone")
		{
			int matoff;
			cin >> matoff;
			CSparseMatrix clone;
			clone = vec.at(matoff);
			vec.push_back(clone);
		}
		else if (s == "rename") //dziala
		{
			int matoff;
			string newName;
			cin >> matoff;
			cin >> newName;
			vec.at(matoff).rename(newName);
			cout << vec.at(matoff).getMatrixName();
		}
		else if (s == "exit")
		{
			exit(0);
		}
	}

	getchar();
    return 0;
}

