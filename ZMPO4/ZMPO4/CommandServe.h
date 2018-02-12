#pragma once
#include "CTree.h"
#define ERROR_CODE "ERROR CODE: "
#define VECTOR_EMPTY "\nERROR - Vector is empty" //-1
#define TREE_EMPTY "\nERROR - Tree does not exist" //-2
#define INCORRECT_ARGS "\nERROR - Incorrect arguments number " //-3
#define DIV_BY_ZERO "\nERROR - Division by 0 " //-4
#define INCORRECT_COMMAND "\nERROR - Incorrect command " //-5

class CommandServe
{
public:
	CommandServe();
	~CommandServe();

	int enter(CTree&, bool&);
	int vars(CTree&, bool&);
	int print(CTree&, bool&);
	int comp(CTree&, bool&);
	int join(CTree&, bool&);
	void exit();
	int incorrect();
	void printErrorCode(int);

};

