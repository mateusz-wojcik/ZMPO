#include "stdafx.h"
#include "Stack.h"

template<class T>
Stack<T>::Stack()
{
}

template<class T>
Stack<T>::Stack(int capacity) : capacity(capacity), top(0), stack(new T[capacity])
{
}

template<class T>
Stack<T>::~Stack()
{
	delete[] stack;
}

template<class T>
std::ostream& operator << (std::ostream& output, Stack<T>& stack)
{
	for (int i = 0; i < stack.top; i++)
	{
		output << stack.stack[i] << " -> ";
	}
	output << "Top";
	return output;
}

template<class T>
void Stack<T>::copyFrom(Stack<T>& other)
{
	while (!this->isFull() && !other.isEmpty())
	{
		this->push(other.pop());
	}
}

template<class T>
void Stack<T>::push(T element)
{
	if (!isFull()) stack[top++] = element;
	else throw FullStackException();
}

template<class T>
T Stack<T>::pop()
{
	if (!isEmpty())	return stack[--top];
	else throw EmptyStackException();

}

template<class T>
bool Stack<T>::isEmpty()
{
	return top == 0;
}

template<class T>
bool Stack<T>::isFull()
{
	return top == capacity;
}
