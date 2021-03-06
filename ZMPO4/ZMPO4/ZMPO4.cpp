#include "stdafx.h"
#include <iostream>
#include <string>
#include "CTree.h"
#include "CommandServe.h"
#include "GeneticProgramming.h"
#include <ctime>

int main()
{
	srand(time(NULL));
	CTree tree;
	CommandServe commandServe;
	GeneticProgramming geneticProgramming;
	bool isCreated = false;
	int excecutionCode = 0;

	while (true)
	{
		std::string command;
		std::cin >> command;
		if (command == "enter")
		{
			excecutionCode = commandServe.enter(tree, isCreated);
		}
		else if (command == "vars")
		{
			excecutionCode = commandServe.vars(tree, isCreated);
		}
		else if (command == "print")
		{
			excecutionCode = commandServe.print(tree, isCreated);
		}
		else if (command == "comp")
		{
			excecutionCode = commandServe.comp(tree, isCreated);
		}
		else if (command == "join")
		{
			excecutionCode = commandServe.join(tree, isCreated);
		}
		else if (command == "mutate")
		{
			tree.mutate();
		}
		else if (command == "randomnode")
		{
			std::cout << tree.findRandomNode(*tree.getRoot()).getValue() << std::endl;
		}
		else if (command == "hyb")
		{
			CTree tmp = CTree(tree);
			tree.hybridize(tmp);
			commandServe.print(tmp, isCreated);
		}
		else if (command == "random")
		{
		    tree = geneticProgramming.createRandomTree();
			isCreated = true;
		}
		else if (command == "initiation")
		{
			geneticProgramming.initiation();
			std::cout << "done" << "\n";
			geneticProgramming.printAll();
		}
		else if (command == "evaluation")
		{
			geneticProgramming.evaluation();
		}
		else if (command == "run")
		{
			geneticProgramming.runIteration();
		}
		else if (command == "exit")
		{
			commandServe.exit();
		}
		else
		{
			excecutionCode = commandServe.incorrect();
		}
		if (excecutionCode != 0) commandServe.printErrorCode(excecutionCode);
	}

	getchar();
	return 0;
}

