#include "Joc.h"
#include "Partida.h"
#include <Windows.h>
#include <iostream>
using namespace std;

//-----------------------------------------
// joc: porta el control de tot el joc
//-----------------------------------------

void joc()
{
	Partida P;//creamos la partida
	Screen jocLib(MIDAX, MIDAY);

	P.newGame(); //Inicializamos la partida.

	P.menu(jocLib);//mostramos el menu por pantalla

	system("cls");//borra la pantalla del menu

	//Mostrem finestra
	jocLib.show();

	//Variables de las coordenadas del ratón.
	int xMouse;
	int yMouse;
	int Click = 0;

	do //se ejecuta el bucle constantemente esperando acontecimientos(clicks) o ESC
	{
		jocLib.processEvents();

		if (Mouse_getButLeft())//detecta si hay click
		{
			xMouse = Mouse_getX();
			yMouse = Mouse_getY();

			if (Click < 2)
			{
				P.processaClick(xMouse, yMouse, Click);//comprueba que el click sea valido
				Click++;
			}
			
			if (P.getMensaje())
				Click = 0;//borra el click si no es valido

			if (Click == 2)
				Click = 0;//reinicia el contador para un nuevo movimiento
		}

		//Visualizamos el tablero pintándolo.

		P.visualitza();
		P.reset(); //Al pulsar la tecla R, se reinicia el tablero, dando el turno a las blancas
		P.acabaPartida(); /*Revisa si alguien gana la partida (si no queda ninguna ficha de alguno de los colores), 
						  y si es asi, muestra la pantalla de victoria de negras o blancas segun corresponda y el sonido*/

		//Actualitza la pantalla

		jocLib.update();

		// ***********************************************************************
		// Sortim del bucle si pressionem ESC
		// ***********************************************************************
	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

	P.SaveGame(jocLib); //guarda los movimientos de la cola(que se ha ido actualizando en cada movimiento correcto) en un fichero
}