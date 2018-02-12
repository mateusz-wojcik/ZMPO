#include "stdafx.h"
#include "CNode.h"
#include <iostream>
#include <string>

CNode::CNode()
{
}

CNode::CNode(std::string val)
{
	value = val;
}

CNode::~CNode()
{
	for (int i = 0; i < getChildrenNumber(); i++)
	{
		delete getChildren().at(i);
	}
}

void CNode::createNode(std::vector<std::string>& expression, std::vector<std::string>::iterator& iterator, int& err)
{
	if (isNumeric(*iterator))
	{
		identity = NUMERIC;
		setChildrenNumber(0);
	}
	else if (isOperator(*iterator))
	{
		identity = OPERATOR;
		setChildrenNumber(2);
	}
	else if (isTrigonometric(*iterator))
	{
		identity = TRIGONOMETRIC;
		setChildrenNumber(1);
	}
	else if (isCorrectVariable(*iterator))
	{
		identity = VARIABLE;
		setChildrenNumber(0);
	}
	else
	{
		value = fixIncorrectVariable(*iterator);
		identity = VARIABLE;
		setChildrenNumber(0);
	}
	setChildren(expression, iterator, err);
}


std::string CNode::fixIncorrectVariable(std::string str)
{
	std::string result;
	for (int i = 0; i < str.length(); i++)
	{
		if (isalpha(str[i]) || isdigit(str[i]))
		{
			result += str[i];
		}
	}
	if (result.length() == 0) result = "a";
	return result;
}

std::string CNode::getValue()
{
	return value;
}

int CNode::getChildrenNumber()
{
	return childrenNumber;
}

std::vector<CNode*> CNode::getChildren()
{
	return children;
}

CNode::Identity CNode::getIdentity()
{
	return identity;
}

bool CNode::isNumeric(const std::string& str)
{
	std::string::const_iterator it = str.begin();
	while (it != str.end() && isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

bool CNode::isOperator(const std::string& str)
{
	return str == "+" || str == "-" || str == "*" || str == "/";
}

bool CNode::isTrigonometric(const std::string& str)
{
	return str == "sin" || str == "cos";
}

bool CNode::isCorrectVariable(const std::string& str)
{
	std::string::const_iterator it = str.begin();
	while (it != str.end() && (isalpha(*it) || isdigit(*it))) ++it;
	return !str.empty() && it == str.end();
}

void CNode::setChildren(std::vector<std::string>& expression, std::vector<std::string>::iterator& iterator, int& err)
{
	for (int i = 0; i < childrenNumber; i++) //rekurencyjnie tworzy kolejne poddrzewa
	{
		if ((iterator != expression.end()) && next(iterator) == expression.end()) //iterator wskazuje na ostatni element
		{
			err = -1; //za ma³o operandów
			children.push_back(new CNode(DEFAULT_VALUE));
			children.at(i)->setIdentity(NUMERIC);
			children.at(i)->setChildrenNumber(0);
		}
		else
		{
			iterator++;
			children.push_back(new CNode(*iterator));
			children.at(i)->createNode(expression, iterator, err);
		}
	}
}

//funkcja pomocnicza, ktora sprawdza, czy iterator wskazuje na ostatni element
std::vector<std::string>::iterator next(std::vector<std::string>::iterator iter)
{
	return ++iter;
}

void CNode::setChildrenNumber(int number)
{
	childrenNumber = number;
}

void CNode::setIdentity(Identity id)
{
	identity = id;
}