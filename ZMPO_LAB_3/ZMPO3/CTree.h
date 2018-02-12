#pragma once
#include "CNode.h"
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

class CTree
{
public:
	CTree();
	~CTree();

	CTree operator + (CTree&);
	void CTree:: operator = (CTree&);

	void clearExpression();
	int compute(CNode*, std::vector<std::pair<std::string, int>>&, int&);
	void connectVariablesAndValues(std::vector<std::string>& variables, std::vector<int>& values, std::vector<std::pair<std::string, int>>& pairs); //tworzy wektor par (laczy zmienne z ich wartosciami)
	void CTree::createExpression(CNode* node); //tworzy expression na podstawie drzewa (odwrotnie)
	void createTree(); //tworzy korzen i rozpoczyna tworzenie drzewa
	void createVectorWithVariables(CNode* node, std::vector<std::string>&); //tworzy wektor ze zmiennymi w kolejnosci prefiksowej (tak jak w vars)
	void CTree::deleteTree();
	CNode& findLeaf(CNode& root);
	std::vector<std::string>& getExpression(); //zwraca vector stringow (wyrazen)
	CNode* getRoot();
	void parse(std::string); //tworzy vector stringow (wyrazen z ktorych tworzone jest drzewo) - expression
	void parseToValues(std::string, std::vector<int>&); //tworzy vector wartosci int na podstawie sczytanej linii
	void postorder(CNode*);
	void preorder(CNode*); //przechodzi drzewo preorderem i wypisuje wyrazenie w postaci prefiksowej
	void printInformation(int);
	void printVariables(CNode*, std::vector<std::string>&);
	int nodeNumber(CNode* node, int level, int currentLevel);

private:
	CNode* root;
	std::vector<std::string> expression;
};

