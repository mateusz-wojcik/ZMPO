#include <vector>
#include <string>
#include <cmath>
#define DEFAULT_VALUE "1"

class CNode
{
public:
	CNode();
	CNode(std::string);
	CNode(CNode&);
	~CNode();

	void operator = (CNode& other);
	friend std::ostream& operator << (std::ostream& output, CNode& node);
	enum Identity { NUMERIC, OPERATOR, TRIGONOMETRIC, VARIABLE };

	void setIdentity(Identity); //ustawia tozsamosc
	void setValue(std::string);
	std::string fixIncorrectVariable(std::string); //usuwa niedozwolone znaki ze zmiennej
	bool isNumeric(const std::string&); //sprawdza czy argument jest liczb�
	bool isOperator(const std::string&); //sprawdza czy argument jest operatorem
	bool isTrigonometric(const std::string&); //sprawdza czy argument jest wartoscia trygonometryczn�
	bool isCorrectVariable(const std::string&); //sprawdza czy argument jest zmienn�
	void createNode(std::vector<std::string>&, std::vector<std::string>::iterator&, int&); //metoda zaczyna parsowac wyrazenie w miejscu aktualnej pozycji iteratora
	std::string getValue(); //zwraca wartosc wez�a
	std::vector<CNode*>& getChildren(); //zwraca wektor wskaznikow do dzieci
	Identity getIdentity(); //zwraca typ wez�a

private:
	std::string value;; //wartosc w�z�a
	std::vector<CNode*> children; //wektor wska�nik�w do dzieci
	Identity identity; //czym jest wezel
};