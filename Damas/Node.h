#include <iostream>
#include "Moviment.h"
using namespace std;

class Node
{
public:

	Node();
	~Node();

	Moviment& getValor() { return N_Valor; }
	Node * getNext() { return N_Next; }
	void setValor(const Moviment& valor) { N_Valor = valor; }
	void setNext(Node * next) { N_Next = next; }

private:

	Moviment N_Valor;
	Node * N_Next;

};

