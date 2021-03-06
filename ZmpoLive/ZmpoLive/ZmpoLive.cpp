#include "stdafx.h"
#include "CProstokat.h"

void testPunktu1()
{
	//CPoint x;
	CPunkt a(1, 1), b(2, 2);
	CPunkt c(3, 3), d(a);

	std::cout << a << b << c << d << std::endl;

	c = b;

	c.setX(10); c.setY(10);
	a.setX(20); a.setY(20);

	std::cout << a << b << c << d << std::endl;
}

void testProstokata1()
{
	CProstokat rect(1, 2, 3, 4);
	CProstokat rect2(5, 6, 7, 8);

	CProstokat rect3 = rect + rect2;
	std::cout << rect3;
}

void testProstokata2()
{
	CPunkt a(1, 1), b(2, 2);
	CPunkt c(3, 3), d(a);
	CProstokat rect(1, 2, 3, 4);
	CProstokat rect2(a, c);
	CProstokat rect3(b, c);
	rect2 = rect + rect2;
	std::cout << rect3;
}


int main()
{
	testProstokata2();

	getchar();
    return 0;
}


