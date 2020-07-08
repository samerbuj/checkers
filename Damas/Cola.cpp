#include "Cola.h"

void Cola::add(Moviment mov)
{
	Node * aux = new Node;

	aux->setValor(mov);

	if (estaVacia())
	{
		C_Primero = aux;
		C_Ultimo = aux; //C_Ultimo->setNext(aux);
	}
	else
	{
		//aux->setNext(C_Ultimo->getNext());
		C_Ultimo->setNext(aux);
		C_Ultimo = aux;
	}

	NuMov++;
}

void Cola::take() //Quita el primer elemento de la cola.
{
	Node * aux;
	
	if (C_Primero->getNext() != NULL)
	{
		aux = C_Primero;
		C_Primero = C_Primero->getNext();
		delete aux;
	}
	else
	{
		aux = C_Primero;
		delete aux;
	}
}