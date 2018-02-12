#include <vector>
#include <string>
#define DEFAULT_VALUE "1"

class CNode
{
public:
	CNode();
	CNode(std::string);
	~CNode();

	enum Identity { NUMERIC, OPERATOR, TRIGONOMETRIC, VARIABLE };

	void createNode(std::vector<std::string>&, std::vector<std::string>::iterator&, int&); //metoda zaczyna parsowac wyrazenie w miejscu aktualnej pozycji iteratora
	std::string getValue();
	int getChildrenNumber();
	std::vector<CNode*> getChildren();
	Identity getIdentity();
	bool isNumeric(const std::string&);
	bool isOperator(const std::string&);
	bool isTrigonometric(const std::string&);
	bool isCorrectVariable(const std::string&);
	std::string fixIncorrectVariable(std::string);
	void CNode::setChildren(std::vector<std::string>&, std::vector<std::string>::iterator&, int&);
	void setChildrenNumber(int); //(liczba argumentow operatora) ustawia liczbe dzieci w zaleznosci od tego jaka jest wartosc wezla(czy jest operatorem, czy liczb¹)
	void setIdentity(Identity);

private:
	std::vector<CNode*> children; //wektor wskaŸników do dzieci
	int childrenNumber; //liczba dzieci wêz³a
	Identity identity; //czym jest weze³
	std::string value;; //wartosc wêz³a
};

