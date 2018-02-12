#include "stdafx.h"
#include "CommandServe.h"


CommandServe::CommandServe()
{
}


CommandServe::~CommandServe()
{
}

int CommandServe::enter(CTree& tree, bool& isCreated)
{
	if (isCreated) del(tree,isCreated);
	std::string exp;
	std::getline(std::cin, exp);
	tree.parse(exp);
	if (tree.getExpression().size() == 0) return -1;
	tree.createTree();

	isCreated = true;
	return 0;
}

int CommandServe::vars(CTree& tree, bool& isCreated)
{
	if (!isCreated) return -2;
	std::vector<std::string> printed;
	tree.printVariables(tree.getRoot(), printed);
	if (printed.size() == 0) std::cout << "0 variables in this tree";
	std::cout << "\n";
	
	return 0;
}

int CommandServe::print(CTree& tree, bool& isCreated)
{
	if (!isCreated) return -2;
	tree.preorder(tree.getRoot());
	std::cout << "\n";
	
	return 0;
}

int CommandServe::comp(CTree& tree, bool& isCreated)
{
	if (!isCreated) return -2;
	int error = 0;
	std::string line;

	std::vector<std::string> variables;
	std::vector<int> values;
	std::vector<std::pair<std::string, int>> variablesWithValues;
	
	tree.createVectorWithVariables(tree.getRoot(), variables);
	std::getline(std::cin, line);
	tree.parseToValues(line, values);
	if (variables.size() != values.size()) return -3;
	tree.connectVariablesAndValues(variables, values, variablesWithValues);
	int result = tree.compute(tree.getRoot(), variablesWithValues, error);
	if (error == 0)	std::cout << result << std::endl;
	else return -4;

	return 0;
}

int CommandServe::join(CTree& tree, bool& isCreated)
{
	if (!isCreated) return -2;

	CTree c_sum, c_a, c_b;
	c_a = tree;

	std::string exp;
	std::getline(std::cin, exp);
	c_b.parse(exp);
	if (c_b.getExpression().size() == 0) return -1;
	c_b.createTree();

	c_sum = c_a + c_b;

	tree.deleteTree();

	tree = c_sum;

	return 0;
}

int CommandServe::del(CTree& tree, bool& isCreated)
{
	if (!isCreated) return -2;
	tree.deleteTree();
	
	isCreated = false;
	return 0;
}
void CommandServe::exit(CTree& tree, bool& isCreated)
{
	if (isCreated) tree.deleteTree();
	std::exit(0);
}

int CommandServe::incorrect()
{
	return -5;
}

void CommandServe::printErrorCode(int err)
{
	switch (err)
	{
	case -1:
		std::cout << ERROR_CODE << err << VECTOR_EMPTY << std::endl;
		break;
	case -2:
		std::cout << ERROR_CODE << err << TREE_EMPTY << std::endl;
		break;
	case -3:
		std::cout << ERROR_CODE << err << INCORRECT_ARGS << std::endl;
		break;
	case -4:
		std::cout << ERROR_CODE << err << DIV_BY_ZERO << std::endl;
		break;
	case -5:
		std::cout << ERROR_CODE << err << INCORRECT_COMMAND << std::endl;
		break;
	}
}