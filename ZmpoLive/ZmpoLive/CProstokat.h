#pragma once
#include "CPunkt.h"
#include <iostream>

class CProstokat
{
public:
	CProstokat(CPunkt&, CPunkt&);
	CProstokat(int, int, int, int);
	~CProstokat();

	friend std::ostream& operator << (std::ostream&, CProstokat&);
	CProstokat operator + (CProstokat& other);

private:
	CPunkt leftBottom;
	unsigned int width;
	unsigned int height;
};

