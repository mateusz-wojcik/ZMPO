#pragma once
#include <iostream>
#include "EmptyStackException.h"
#include "FullStackException.h"

template<class T>
class Stack
{
public:
	Stack();
	Stack(int);
	~Stack();

	template<class T>
	friend std::ostream& operator << (std::ostream&, Stack<T>&);
	void copyFrom(Stack&);

	void push(T);
	T pop();
	bool isEmpty();
	bool isFull();

private:
	T* stack;
	int top;
	int capacity;
};

