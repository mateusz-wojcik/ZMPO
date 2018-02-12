#include "stdafx.h"
#include "GeneticProgramming.h"


GeneticProgramming::GeneticProgramming()
{
}


GeneticProgramming::~GeneticProgramming()
{
}

std::string createRandomElement()
{
	std::string element;
	int valueRange = 10;
	int option = rand() % 11 + 1;
	switch (option)
	{
	case 1:
		element = "+";
		break;
	case 2:
		element = "-";
		break;
	case 3:
		element = "/";
		break;
	case 4:
		element =  "*";
		break;
	case 5:
		element =  "sin";
		break;
	case 6:
		element = "cos";
		break;
	case 7:
		element =  "x";
		break;
	case 8:
		element =  "y";
		break;
	default:
		element =  std::to_string(rand() % valueRange);
		break;
	}

	return element;
}

void incrementIterator(int& iter, std::string argument)
{
	if (argument == "+" || argument == "-" || argument == "*" || argument == "/")
	{
		iter += 2;
	}
	else if (argument == "sin" || argument == "cos")
	{
		iter++;
	}
}

bool isTooLong(int length)
{
	if (length > 50) return true;
	return false;
}

std::string createRandomExpression()
{
	std::stringstream expression;
	std::string element;
	int iter = 1;
	do
	{
		element = createRandomElement();
		expression << element << " ";
		incrementIterator(iter, element);
		iter--;
		if (isTooLong(expression.str().length())) iter = 0;
	} while (iter > 0);

	return expression.str();
}

CTree GeneticProgramming::createRandomTree()
{
	CTree tree(createRandomExpression());
	return tree;
}

void GeneticProgramming::initiation()
{
	clearPopulation();
	clearParentsPopulation();
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		population.push_back(new CTree(createRandomExpression()));
	}
}

void split(const std::string& str, std::vector<std::string>& fileLineVector, char delimiter)
{
	std::stringstream ss(str);
	std::string token;
	fileLineVector.clear();
	while (std::getline(ss, token, delimiter))
	{
		fileLineVector.push_back(token);
	}
}

void GeneticProgramming::clearPopulation()
{
	for (int i = 0; i < population.size(); i++)
	{
		delete population.at(i);
	}
	population.clear();
}

void GeneticProgramming::clearParentsPopulation()
{
	for (int i = 0; i < parentsPopulation.size(); i++)
	{
		delete parentsPopulation.at(i);
	}
	parentsPopulation.clear();
}

void GeneticProgramming::evaluation()
{
	//std::ifstream file("Data.txt");
	std::string line;
	std::vector<double> values;
	values.push_back(0);
	values.push_back(0);
	std::vector<std::string> variables;
	variables.push_back("x");
	variables.push_back("y");
	std::vector<std::pair<std::string, double>> variablesWithValues;
	std::vector<std::string> fileLineVector;
	double adaptationValue = 0;
	int error = 0;
	std::ifstream dataFile("Data.txt");
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (dataFile.is_open())
		{
			population.at(i)->setAdaptationValue(0);
			while (std::getline(dataFile, line))
			{
				split(line, fileLineVector, ';');
				values.at(0) = stof(fileLineVector.at(0)); //double required
				values.at(1) = stof(fileLineVector.at(1));
 				population.at(i)->connectVariablesAndValues(variables, values, variablesWithValues);
				adaptationValue += pow( stod(fileLineVector.at(2)) - ((*population.at(i)).compute(population.at(i)->getRoot(), variablesWithValues, error)), 2);
			}
			if (adaptationValue == 0)
			{
				population.at(i)->preorder();
			    std::cout << std::endl;
				//std::cout << population.at(i)->expressionToString() << "---------------------------------------------------------------\n";
			}
			population.at(i)->setAdaptationValue(adaptationValue);
			adaptationValue = 0;
		}
		dataFile.clear();
		dataFile.seekg(0, std::iostream::beg);
	}
	dataFile.close();
}

void GeneticProgramming::selection()
{
	for (int i = 0; i < TOURNAMENT_NUMBER; i++)
	{
		int tree1Index = rand() % population.size();
		int tree2Index = rand() % population.size();
		if (population.at(tree1Index)->getAdaptationValue() >= population.at(tree2Index)->getAdaptationValue())
		{
			parentsPopulation.push_back(new CTree(*population.at(tree1Index)));
		}
		else
		{
			parentsPopulation.push_back(new CTree(*population.at(tree2Index)));
		}
	}
}

void GeneticProgramming::hybridize()
{
	for (int i = 0; i < parentsPopulation.size() / 2; i++)
	{
		if (rand() % 100 + 1 < HYBRIDIZE_PROBABILITY)
		{
			parentsPopulation.at(i*2)->hybridize(*parentsPopulation.at(std::abs(i * 2 - 1)));
		}
		population.push_back(new CTree(*parentsPopulation.at(i * 2)));
	    population.push_back(new CTree(*parentsPopulation.at(std::abs(i * 2 - 1))));
	}
}

void GeneticProgramming::mutation()
{
	for (int i = 0; i < population.size(); i++)
	{
		if (rand() % 100 + 1 < MUTATION_PROBABILITY)
		{
			population.at(i)->mutate();
		}
	}
}

CTree GeneticProgramming::getBestTree(std::vector<CTree*>& population)
{
	auto minTree = std::min_element(population.begin(), population.end(), [](CTree* a, CTree* b) {return (*a).getAdaptationValue() < (*b).getAdaptationValue();});
	return **minTree;
}

void GeneticProgramming::printAll()
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		population.at(i)->preorder();
		//std::cout << population.at(i)->expressionToString() << std::endl;
	}
}

void GeneticProgramming::runIteration()
{
	initiation();
	evaluation();
	for (int i = 0; i < ITEARTIONS_NUMBER; i++)
	{
		selection();
		hybridize();
		mutation();
		evaluation();
	}
	CTree tree = getBestTree(population);
	tree.preorder();
	//std::cout << tree. << " which value is: " << tree.getAdaptationValue() <<"\n";
}


