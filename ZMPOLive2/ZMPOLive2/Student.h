#pragma once
#include <string>

class Student
{
public:
	Student();
	Student(std::string, int);
	~Student();

	friend std::ostream& operator << (std::ostream&, Student&);

private:
	std::string name;
	int year;

};

