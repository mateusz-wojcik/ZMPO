#include "stdafx.h"
#include "Stack.h"
#include "Stack.cpp"
#include "Student.h"

void test1()
{
	Stack<int> stack(5);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	std::cout << stack << "\n";
	stack.push(6); //full stack exception
	stack.pop();
	std::cout << stack << "\n";
	stack.pop();
	stack.pop();
	stack.pop();
	std::cout << stack << "\n";
}

void test2()
{
	Stack<Student> studStack(5);
	studStack.push(Student("Student1", 1997));
	studStack.push(Student("Student2", 1990));
	studStack.push(Student("Student3", 1991));
	studStack.push(Student("Student4", 1992));
	std::cout << studStack << "\n";
	studStack.pop();
	std::cout << studStack << "\n";
	studStack.push(Student("Kolega", 2001));
	std::cout << studStack << "\n";
}

void test3()
{
	Stack<int> stack(5);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	//stack.push(6);// full stack exception
	std::cout << stack << "\n";
	stack.pop();
	std::cout << stack << "\n";
	stack.pop();
	stack.pop();
	stack.pop();
	std::cout << stack << "\n";

	Stack<int> helpStack(5);
	helpStack.push(20);
	helpStack.push(30);
	helpStack.push(40);
	helpStack.push(50);
	std::cout << helpStack << "\n";

	stack.copyFrom(helpStack);
	std::cout << stack << "\n";
	std::cout << helpStack << "\n";
}

void test4()
{
	Stack<std::string> stack(2);
	stack.push("a");
	stack.push("b");
	stack.pop();
	stack.pop();
	stack.pop();
}

int main()
{
	try {
		test1();
	}
	catch (FullStackException& fse) {
		std::cout << fse.getError() << std::endl;
	}

	test2();
	
	test3();

	try {
		test4();
	}
	catch (EmptyStackException& ese) {
		std::cout << ese.getError() << std::endl;
	}

	getchar();
    return 0;
}

