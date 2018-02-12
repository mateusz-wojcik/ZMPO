#pragma once
#include "CTree.h"
#include <fstream>
#define POPULATION_SIZE 1000
#define ITEARTIONS_NUMBER 1
#define TOURNAMENT_NUMBER 500
#define HYBRIDIZE_PROBABILITY 50 //%
#define MUTATION_PROBABILITY 50 //%

class GeneticProgramming
{
public:
	GeneticProgramming();
	~GeneticProgramming();

	void clearPopulation();
	void clearParentsPopulation();
	CTree createRandomTree();
	CTree getBestTree(std::vector<CTree*>&);
	void printAll();

	void initiation();
	void evaluation();
	void selection();
	void hybridize();
	void mutation();

	void runIteration();

private:
	std::vector<CTree*> population;
	std::vector<CTree*> parentsPopulation;

};

