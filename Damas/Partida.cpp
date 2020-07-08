#include "Partida.h"

Partida::Partida()
{
}

Partida::~Partida()
{
}

void Partida::visualitza()
{
	T.Dibuixa(P_Torn, T.getIfMensaje()); //Dibuja el tablero y marca si debe pintar el mensaje;
}

void Partida::processaClick(int xMouse, int yMouse, int click)
{
	//bool Click = false;

	if (Mouse_getButLeft())
	{
		if (click < 1)//si es el primer click
		{
			T.validaClick(xMouse, yMouse, P_PosFilaOrigen, P_PosColumnaOrigen);//comprueba que esté dentro de los limites del tablero

			P_PosFilaOrigen -= 1;
			P_PosColumnaOrigen -= 1;

			if (!T.estaVacia(P_PosFilaOrigen, P_PosColumnaOrigen))//Comprueba si la casilla esta vacía.
			{
				if (T.checkOrigenValid(P_PosFilaOrigen, P_PosColumnaOrigen, P_Torn) == true)
				{ 
					click = 1;
					T.marcaCasella(P_PosFilaOrigen, P_PosColumnaOrigen, P_Torn);//Marca la casilla como seleccionada.

					if (getMensaje())
						setMensajeOFF();
				}
				else //si la casilla no corresponde a una casilla de origen valido (tiene en cuenta el turno) muestra error
					setMensajeON();
			}
			else //si la casilla está vacía muestra el mensaje de error
				setMensajeON();
		}
		else//si es el segundo click
		{
			T.validaClick(xMouse, yMouse, P_PosFilaDestino, P_PosColumnaDestino);//comprueba que esté dentro de los limites del tablero

			P_PosFilaDestino -= 1;
			P_PosColumnaDestino -= 1;
			click = 2;
			//ferMoviment(); Se realiza al comprobarlo en canviaTorn() para el if interno.
			canviaTorn();//cambia el turno.
		}
	}
}

bool Partida::ferMoviment()
{
	return T.processaMoviment(P_PosFilaOrigen, P_PosColumnaOrigen, P_PosFilaDestino, P_PosColumnaDestino, P_Torn);//realiza el movimiento respetando las reglas del juego
}

void Partida::canviaTorn()
{
	if (ferMoviment())
	{
		if (P_Torn == TORN_BLANC)
			P_Torn = TORN_NEGRE;
		else
			if (P_Torn == TORN_NEGRE)
				P_Torn = TORN_BLANC;
	}
}

void Partida::acabaPartida() //Pinta los sprites del ganador.
{
	if (T.acabaPartida() == FITXA_BLANCA)
	{
		T.NegrasGanan.draw(0, 0);

		Sleep(100);

		T.WinSound();
	}
	else
		if (T.acabaPartida() == FITXA_NEGRA)
		{
			T.BlancasGanan.draw(0, 0);

			Sleep(100);

			T.WinSound();
		}
}

void Partida::menu(Screen & jocLib)
{
	int Option = NULL;

	while ((Option != 1) && (Option != 2))
	{
		cout << "¿Qué quieres jugar?" << endl << endl << "New Game - 1" << endl << "Load Game - 2" << endl << endl;
		cin >> Option; cout << endl;

		switch (Option)
		{
		case 1:
			break;//seguiremos con el proceso normal de joc.cpp ya que empezaremos de cero sin cargar ningún movimiento

		case 2:
			jocLib.show();

			loadGame();//recupera los movimientos guardados en un fichero y los guarda en 

			for (int i = 0; i < getSize(); i++)
			{
				visualitza();//Actualizamos el tablero, para que se vea la realización del movimiento.
				acabaPartida(); 
				jocLib.update();

				marcaMovimiento(i);//

				Sleep(200);

				visualitza();
				acabaPartida(); //Actualizamos el tablero, para que se vea la selección de la casilla.
				jocLib.update();

				setMovimientos(i);

				Sleep(500);
			}
			break;

		default:
			cout << "Escoja una opción valida siusplau." << endl << endl;
			break;
		}
	}
}

void Partida::reset()
{
	if (T.reset())
		P_Torn = TORN_BLANC;
}