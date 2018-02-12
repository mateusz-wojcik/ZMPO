#pragma once
#include <iostream>

class CPunkt
{
public:
	CPunkt(int, int);
	CPunkt(CPunkt&);
	~CPunkt();


	friend std::ostream& operator << (std::ostream&, CPunkt&);
	CPunkt& operator = (CPunkt&);

	int getX();
	int getY();
	void setX(int);
	void setY(int);

private:
	int* x;
	int* y;
};

