#include "Node.h"
#include "Moviment.h"

class Cola
{ 
public:

	Cola() { C_Primero = NULL; C_Ultimo = NULL; NuMov = 0; };
	//~Cola();

	void add(Moviment mov);
	void take();
	Moviment getPrimero() { return C_Primero->getValor(); };
	Moviment getUltimo() { return C_Ultimo->getValor(); };
	bool estaVacia() { return (C_Primero == NULL); };
	int getSize() { return NuMov; };

private:
	
	int NuMov;
	Node * C_Primero, *C_Ultimo;

};