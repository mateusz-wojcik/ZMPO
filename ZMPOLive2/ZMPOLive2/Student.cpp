#include "stdafx.h"
#include "Student.h"


Student::Student()
{
}

Student::Student(std::string name, int year) : name(name), year(year)
{
}

Student::~Student()
{
}

std::ostream& operator << (std::ostream& output, Student& student)
{
	output << student.name << " " << student.year;
	return output;
}