#include "stdafx.h"
#include "CTree.h"
#include <queue>

CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::deleteTree()
{
	delete root;
}

CTree CTree:: operator + (CTree& other)
{
	CTree newTree;
	newTree.createExpression(root);
	newTree.createTree();

	CNode& leaf = findLeaf(*(newTree).getRoot());
	leaf = *(other.getRoot());
	leaf.setIdentity((*(other.getRoot())).getIdentity());

	return newTree;
}

void CTree:: operator = (CTree& other)
{
	this->clearExpression();
	this->createExpression(other.getRoot());
	this->createTree();

	//root = other.getRoot();
}

void CTree::clearExpression()
{
	expression.clear();
}

//oblicza wyrazenie   wezel, vector(zmienna,wartosc zmiennej)
int CTree::compute(CNode* node, std::vector<std::pair<std::string, int>>& variables, int& error)
{
	if (node->getIdentity() == node->VARIABLE)
	{
		for (std::vector<std::pair<std::string, int>>::const_iterator i = variables.begin(); i != variables.end(); ++i)
		{
			if (std::get<0>(*i) == node->getValue())
			{
				return std::get<1>(*i);
			}
		}
	}
	else if (node->getIdentity() == node->NUMERIC)
	{
		return atoi((node->getValue()).c_str());
	}
	else if (node->getIdentity() == node->OPERATOR)
	{
		std::string op = node->getValue();
		if (op == "+") return compute(node->getChildren().at(0), variables, error) + compute(node->getChildren().at(1),variables, error);
		if (op == "-") return compute(node->getChildren().at(0), variables, error) - compute(node->getChildren().at(1), variables, error);
		if (op == "*") return compute(node->getChildren().at(0), variables, error) * compute(node->getChildren().at(1), variables, error);
		if (op == "/")
		{
			if (node->getChildren().at(1)->getValue() == "0" || compute(node->getChildren().at(1), variables, error) == 0)
			{
				error = -1;
				return 0;
			}
			else
			{
		        return compute(node->getChildren().at(0), variables, error) / compute(node->getChildren().at(1), variables, error);
			}
		}
	}
	else if (node->getIdentity() == node->TRIGONOMETRIC)
	{
		std::string fun = node->getValue();
		if (fun == "sin") return sin(atoi(node->getValue().c_str()));
		if (fun == "cos") return cos(atoi(node->getValue().c_str()));
	}
}

//tworzy wektor par
void CTree::connectVariablesAndValues(std::vector<std::string>& variables, std::vector<int>& values, std::vector<std::pair<std::string, int>>& pairs)
{
	for (int i = 0; i < variables.size(); i++)
	{
		pairs.push_back(std::make_pair(variables.at(i), values.at(i)));
	}
}

//tworzy vector, w ktorym sa wartosci wezlow danego drzewa (kopiuje je do expression)
void CTree::createExpression(CNode* node)
{
	expression.push_back(node->getValue());
	for (int i = 0; i < node->getChildrenNumber(); i++)
	{
		createExpression(node->getChildren().at(i));
	}
}

//ustawia wartosc korzenia i rozpoczyna tworzenie drzewa
void CTree::createTree()
{
	int err = 0;
	std::vector<std::string>::iterator iterator = expression.begin();
	root = new CNode(*iterator);
	root->createNode(expression, iterator, err);
	if (err != 0) printInformation(err);
}

//tworzy vector ze zmiennymi
void CTree::createVectorWithVariables(CNode* node, std::vector<std::string>& variables)
{
	if (node->getIdentity() == node->VARIABLE)
	{
		if (std::find(variables.begin(), variables.end(), node->getValue()) == variables.end())
		{
			variables.push_back(node->getValue());
		}
	}
	for (int i = 0; i < node->getChildrenNumber(); i++)
	{
		createVectorWithVariables(node->getChildren().at(i), variables);
	}
}

//znajduje pierwszy lisc przechodzac preorderem
CNode& CTree::findLeaf(CNode& root)
{
	if (root.getIdentity() == root.NUMERIC || root.getIdentity() == root.VARIABLE)
	{
		return root;
	}
	else
	{
		return findLeaf(*(root.getChildren().at(0)));
	}
}

//zwraca korzen drzewa
CNode* CTree::getRoot()
{
	return root;
}

//zwraca przez referencje vector wyra¿eñ
std::vector<std::string>& CTree::getExpression()
{
	return expression;
}

//parsuje stringa i tworzy na jego podstawie vector stringow (wyra¿eñ u¿ytych do tworzenia drzewa)
void CTree::parse(std::string input)
{
	clearExpression();
	std::istringstream iss(input);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(expression));
}

//tworzy wektor wartosci na podstawie sczytanej linii
void CTree::parseToValues(std::string input, std::vector<int>& values)
{
	std::istringstream iss(input);
	int value;
	while (iss >> value) values.push_back(value);
}

//przechodzi drzewo preorderem
void CTree::postorder(CNode* node)
{
	for (int i = 0; i < node->getChildrenNumber(); i++)
	{
		postorder(node->getChildren().at(i));
	}
	std::cout << node->getValue() << " ";
}

//przechodzi drzewo preorderem
void CTree::preorder(CNode* node)
{
	std::cout << node->getValue() << " ";
	for (int i = 0; i < node->getChildrenNumber(); i++)
	{
		preorder(node->getChildren().at(i));
	}
}

void CTree::printInformation(int err)
{
	if(err == -1) std::cout << "Not enough operands - default tree fixing (value: " << DEFAULT_VALUE << ")" << std::endl;
}

//wypisuje wszystkie zmienne w drzewie
void CTree::printVariables(CNode* node, std::vector<std::string>& printed)
{
	if (node->getIdentity() == node->VARIABLE)
	{
		if (std::find(printed.begin(), printed.end(), node->getValue()) == printed.end())
		{
			printed.push_back(node->getValue());
			std::cout << node->getValue() << " ";
		}
	}
	for (int i = 0; i < node->getChildrenNumber(); i++)
	{
		printVariables(node->getChildren().at(i), printed);
	}
}


int CTree::nodeNumber(CNode* node, int level, int currentLevel)
{
	if (level == currentLevel)
	{
		return 1;
	}
	else if (node->getChildrenNumber() > 0)
	{
		int result = 0;
		currentLevel++;
		for (int i = 0; i < node->getChildrenNumber(); i++)
		{
			result += nodeNumber(node->getChildren().at(i), level, currentLevel);
		}
		return result;
	}
	else return 0;

}