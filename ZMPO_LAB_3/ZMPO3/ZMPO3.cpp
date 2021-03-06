#include "stdafx.h"
#include <iostream>
#include <string>
#include "CTree.h"
#include "CommandServe.h"

int main()
{
	CTree tree;
	CommandServe commandServe;
	bool isCreated = false;
	int excecutionCode = 0;
	
	std::cout << ">> ";

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
		else if (command == "del")
		{
			excecutionCode = commandServe.del(tree, isCreated);
		}
		else if (command == "exit")
		{
			commandServe.exit(tree, isCreated);
		}
		else if (command == "cls")
		{
			system("cls");
		}
		else if (command == "level")
		{
			//int currentLevel = 1;
			int level;
			std::cin >> level;
			std::cout << tree.nodeNumber(tree.getRoot(), level, 1) << std::endl;
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

