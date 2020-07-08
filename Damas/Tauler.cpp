#include "Tauler.h"

Tauler::Tauler()
{
}

Tauler::~Tauler()
{
}

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//

bool Tauler::estaVacia(int PosicionI, int PosicionJ)
{ //Comprueba si la casilla esta vacía.
	if (T_MatrizTablero[PosicionI][PosicionJ] == BUIT)
		return true;
	else
		return false;
}

void Tauler::OcuparPosicion(int PosicionI, int PosicionJ, int turno)//int(&Matrix)[MIDATAULER][MIDATAULER],
{ 
	//Procedimiento que ocupa la casilla seleccionada con el jugador.
	if (turno == TORN_BLANC)
		T_MatrizTablero[PosicionI][PosicionJ] = FITXA_BLANCA;
	else 
		if (turno == TORN_NEGRE)
			T_MatrizTablero[PosicionI][PosicionJ] = FITXA_NEGRA;
}

void Tauler::OcuparPosicionDama(int PosicionI, int PosicionJ, int turno)//int(&Matrix)[MIDATAULER][MIDATAULER],
{
	//Procedimiento que ocupa la casilla seleccionada con el jugador.
	if (turno == TORN_BLANC)
		T_MatrizTablero[PosicionI][PosicionJ] = DAMA_BLANCA;
	else
		if (turno == TORN_NEGRE)
			T_MatrizTablero[PosicionI][PosicionJ] = DAMA_NEGRA;
}

void Tauler::setIfMensaje(bool Mensaje) //Procedimiento que cambia el valor para mostrar del mensaje de error.
{
	T_Mensaje = Mensaje;
	
	if (Mensaje)
		ErrorSound();
}

void Tauler::DesocuparPosicion(int PosicionI, int PosicionJ) //int(&Matrix)[MIDATAULER][MIDATAULER],
{ 
	//Desocupa la casilla.
	T_MatrizTablero[PosicionI][PosicionJ] = BUIT;
}

bool Tauler::esCapturable(int FO, int CO, int FD, int CD, int turno)//comprueba si una ficha esta en posición de ser comida según las reglas del juego de las damas
{ 	
	bool cNegraCapturable = (((FD == FO - 2) && ((CD == CO + 2) || (CD == CO - 2))) && ((T_MatrizTablero[FO - 1][CO + 1] == FITXA_NEGRA) || (T_MatrizTablero[FO - 1][CO - 1] == FITXA_NEGRA) || (T_MatrizTablero[FO - 1][CO + 1] == DAMA_NEGRA) || (T_MatrizTablero[FO - 1][CO - 1] == DAMA_NEGRA)));
	bool cBlancaCapturable = (((FD == FO + 2) && ((CD == CO + 2) || (CD == CO - 2))) && ((T_MatrizTablero[FO + 1][CO + 1] == FITXA_BLANCA) || (T_MatrizTablero[FO + 1][CO - 1] == FITXA_BLANCA) || (T_MatrizTablero[FO + 1][CO + 1] == DAMA_BLANCA) || (T_MatrizTablero[FO + 1][CO - 1] == DAMA_BLANCA)));
	
	if (turno == TORN_BLANC)
	{
		if (T_MatrizTablero[FO][CO] == FITXA_BLANCA_SEL)
		{
			if (cNegraCapturable)
				return true;
			else
				return false;
		}
	}
	else
		if (turno == TORN_NEGRE)
		{
			if (T_MatrizTablero[FO][CO] == FITXA_NEGRA_SEL)
			{
				if (cBlancaCapturable)
					return true;
				else
					return false;
			}
		}
}

bool Tauler::esCapturableDama(int FO, int CO, int FD, int CD, int turno)//hace lo mismo que la funcion anterior pero con las damas
{
	bool DamaCapturarPositivo = (((((FD == FO - 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO - 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO - 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO - 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO - 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO - 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO - 7) && ((CD == CO + 7) || (CD == CO - 7))))));
	bool DamaCapturarNegativo = (((((FD == FO + 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO + 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO + 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO + 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO + 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO + 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO + 7) && ((CD == CO + 7) || (CD == CO - 7))))));
	int Contador = 0, i, j, DamaCapturadora, DamaCapturable, FitxaCapturable,FitxaNOCapturable;

	if (turno == TORN_BLANC)
	{
		DamaCapturadora = DAMA_BLANCA;
		DamaCapturable = DAMA_NEGRA;
		FitxaCapturable = FITXA_NEGRA;
		FitxaNOCapturable = FITXA_BLANCA;
	}
	else
		if (turno == TORN_NEGRE)
		{
			DamaCapturadora = DAMA_NEGRA;
			DamaCapturable = DAMA_BLANCA;
			FitxaCapturable = FITXA_BLANCA;
			FitxaNOCapturable = FITXA_NEGRA;
		}

		if (T_MatrizTablero[FO][CO] == DamaCapturadora)
		{
			if (estaVacia(FD, CD))
			{
				if (DamaCapturarPositivo)
				{
					if (CD > CO)
					{
						for (i = FO - 1, j = CO + 1; i > FD, j < CD; i--, j++)
						{
							if ((T_MatrizTablero[i][j] == FitxaCapturable) || (T_MatrizTablero[i][j] == DamaCapturable))
							{
								Contador++;

								if ((FD == i - 1) && (CD == j + 1))
									return true;
								else
									return false;
							}
							else
								if ((T_MatrizTablero[i][j] == FitxaNOCapturable) || (T_MatrizTablero[i][j] == DamaCapturadora))
									return false;
						}
					}
					else
						if (CD < CO)
						{
							for (i = FO - 1, j = CO - 1; i > FD, j > CD; i--, j--)
							{
								if ((T_MatrizTablero[i][j] == FitxaCapturable) || (T_MatrizTablero[i][j] == DamaCapturable))
								{
									Contador++;

									if ((FD == i - 1) && (CD == j - 1))
										return true;
									else
										return false;
								}
								else
									if ((T_MatrizTablero[i][j] == FitxaNOCapturable) || (T_MatrizTablero[i][j] == DamaCapturadora))
										return false;
							}
						}
				}
				else
					if (DamaCapturarNegativo)
					{
						if (CD > CO)
						{
							for (i = FO + 1, j = CO + 1; i < FD, j < CD; i++, j++)
							{
								if ((T_MatrizTablero[i][j] == FitxaCapturable) || (T_MatrizTablero[i][j] == DamaCapturable))
								{
									Contador++;

									if ((FD == i + 1) && (CD == j + 1))
										return true;
									else
										return false;
								}
								else
									if ((T_MatrizTablero[i][j] == FitxaNOCapturable) || (T_MatrizTablero[i][j] == DamaCapturadora))
										return false;
							}
						}
						else
							if (CD < CO)
							{
								for (i = FO + 1, j = CO - 1; i < FD, j > CD; i++, j--)
								{
									if ((T_MatrizTablero[i][j] == FitxaCapturable) || (T_MatrizTablero[i][j] == DamaCapturable))
									{
										Contador++;

										if ((FD == i + 1) && (CD == j - 1))
											return true;
										else
											return false;
									}
									else
										if ((T_MatrizTablero[i][j] == FitxaNOCapturable) || (T_MatrizTablero[i][j] == DamaCapturadora))
											return false;
								}
							}
					}
			}
			else
				return false;
		}
}

void Tauler::Captura(int FO, int CO, int FD, int CD, int turno)
{
	int Fila, Columna;

	if (turno == TORN_BLANC)
	{
		if (T_MatrizTablero[FO][CO] == FITXA_BLANCA_SEL)
		{
			Fila = ((FD + FO) / 2);
			Columna = ((CD + CO) / 2);
		}
		else
			if (T_MatrizTablero[FO][CO] == DAMA_BLANCA)
			{
				if (FD > FO)
				{
					Fila = FD - 1;

					if (CD > CO)
						Columna = CD - 1;
					else
						if (CD < CO)
							Columna = CD + 1;
				}
				else
					if (FD < FO)
					{
						Fila = FD + 1;

						if (CD > CO)
							Columna = CD - 1;
						else
							if (CD < CO)
								Columna = CD + 1;
					}
			}
	}
	else
		if (turno == TORN_NEGRE)
		{
			if (T_MatrizTablero[FO][CO] == FITXA_NEGRA_SEL)
			{
				Fila = ((FD + FO) / 2);
				Columna = ((CD + CO) / 2);
			}
			else
				if (T_MatrizTablero[FO][CO] == DAMA_NEGRA)
				{
					if (FD > FO)
					{
						Fila = FD - 1;

						if (CD > CO)
							Columna = CD - 1;
						else
							if (CD < CO)
								Columna = CD + 1;
					}
					else
						if (FD < FO)
						{
							Fila = FD + 1;

							if (CD > CO)
								Columna = CD - 1;
							else
								if (CD < CO)
									Columna = CD + 1;
						}
				}
		}
	
	DesocuparPosicion(Fila, Columna);
	PopSound();
}

void Tauler::Transforma(int PosI, int PosJ, int turno)
{
	//Transformamos la casilla que llega al lado opuesto en una dama.

	if (turno == TORN_BLANC)
		T_MatrizTablero[PosI][PosJ] = DAMA_BLANCA;
	else
		if (turno == TORN_NEGRE)
			T_MatrizTablero[PosI][PosJ] = DAMA_NEGRA;

	TransformationSound();
}

void Tauler::MovimientoCasillaBlanca(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner)
{
	if (MOV_BLANC(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti))
	{
		if (estaVacia(FilaDesti, ColumnaDesti)) //Hace el movimiento si entra.
		{
			DesocuparPosicion(FilaOrigen, ColumnaOrigen);
			OcuparPosicion(FilaDesti, ColumnaDesti, torn);
			Returner = true;
			MoveSound();
		}
		else
		{
			setIfMensaje(true); //Avisa si el movimiento es inválido.
			desmarcaCasella(FilaOrigen, ColumnaOrigen, torn);
		}
	}
	else
		if (esCapturable(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn)) //Comprueba que se pueda hacer la captura.
		{
			if (estaVacia(FilaDesti, ColumnaDesti)) //Hace el movimiento si entra.
			{
				Captura(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn);
				DesocuparPosicion(FilaOrigen, ColumnaOrigen);
				OcuparPosicion(FilaDesti, ColumnaDesti, torn);
				Returner = true;
			}
		}
		else
		{
			setIfMensaje(true); //Avisa si el movimiento es inválido.
			desmarcaCasella(FilaOrigen, ColumnaOrigen, torn);
		}
}

void Tauler::MovimientoCasillaNegra(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner)
{
	if (MOV_NEGRE(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti))
	{
		if (estaVacia(FilaDesti, ColumnaDesti))
		{
			DesocuparPosicion(FilaOrigen, ColumnaOrigen);
			OcuparPosicion(FilaDesti, ColumnaDesti, torn);
			Returner = true;
			MoveSound();
		}
		else
		{
			setIfMensaje(true); //Avisa si el movimiento es inválido.
			desmarcaCasella(FilaOrigen, ColumnaOrigen, torn);
		}
	}
	else
		if (esCapturable(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn)) //Comprueba que se pueda hacer la captura.
		{
			if (estaVacia(FilaDesti, ColumnaDesti)) //Hace el movimiento si entra.
			{
				Captura(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn);
				DesocuparPosicion(FilaOrigen, ColumnaOrigen);
				OcuparPosicion(FilaDesti, ColumnaDesti, torn);
				Returner = true;
			}
		}
		else
		{
			setIfMensaje(true); //Avisa si el movimiento es inválido.
			desmarcaCasella(FilaOrigen, ColumnaOrigen, torn);
		}
}

void Tauler::MovimientoDamaBlanca(int FO, int CO, int FD, int CD, int torn, bool & Returner)
{
	//movimientos posibles de una dama
	bool MovPositivo = (((FD == FO - 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO - 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO - 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO - 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO - 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO - 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO - 7) && ((CD == CO + 7) || (CD == CO - 7))));
	bool MovNegativo = (((FD == FO + 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO + 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO + 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO + 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO + 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO + 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO + 7) && ((CD == CO + 7) || (CD == CO - 7))));
	bool Obstaculo = false;

	if (MovPositivo || MovNegativo)
	{
		if (MovPositivo)
		{
			if (estaVacia(FD, CD))
			{
				int i = 0, j = 0;

				while ((FO - i > FD) && (CO + j < CD) && (!Obstaculo)) //Hace una comprobación en diagonal del movimiento para ver si hay alguna casilla.
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO - i][CO + j] == FITXA_BLANCA) || (T_MatrizTablero[FO - i][CO + j] == DAMA_BLANCA) || (T_MatrizTablero[FO - i][CO + j] == FITXA_NEGRA) || (T_MatrizTablero[FO - i][CO + j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				while ((FO - i > FD) && (CO - j > CD) && (!Obstaculo))
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO - i][CO - j] == FITXA_BLANCA) || (T_MatrizTablero[FO - i][CO - j] == DAMA_BLANCA) || (T_MatrizTablero[FO - i][CO - j] == FITXA_NEGRA) || (T_MatrizTablero[FO - i][CO - j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				if (!Obstaculo)
				{
					DesocuparPosicion(FO, CO);
					OcuparPosicionDama(FD, CD, torn);
					Returner = true;
					MoveSound();
				}

				if (esCapturableDama(FO, CO, FD, CD, torn)) //Comprueba que se pueda hacer la captura.
				{
					if (estaVacia(FD, CD)) //Hace el movimiento si entra.
					{
						setIfMensaje(false);
						Captura(FO, CO, FD, CD, torn);
						DesocuparPosicion(FO, CO);
						OcuparPosicionDama(FD, CD, torn);
						Returner = true;
					}
				}
			}
			else
			{
				setIfMensaje(true); //Avisa si el movimiento es inválido.
				desmarcaCasella(FO, CO, torn);
			}
		}

		if (MovNegativo)
		{
			if (estaVacia(FD, CD))
			{
				int i = 0, j = 0;

				while ((FO + i < FD) && (CO + j < CD) && (!Obstaculo)) //Hace una comprobación en diagonal del movimiento para ver si hay alguna casilla.
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO + i][CO + j] == FITXA_BLANCA) || (T_MatrizTablero[FO + i][CO + j] == DAMA_BLANCA) || (T_MatrizTablero[FO + i][CO + j] == FITXA_NEGRA) || (T_MatrizTablero[FO + i][CO + j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				while ((FO + i < FD) && (CO - j > CD) && (!Obstaculo))
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO + i][CO - j] == FITXA_BLANCA) || (T_MatrizTablero[FO + i][CO - j] == DAMA_BLANCA) || (T_MatrizTablero[FO + i][CO - j] == FITXA_NEGRA) || (T_MatrizTablero[FO + i][CO - j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				if (!Obstaculo)
				{
					DesocuparPosicion(FO, CO);
					OcuparPosicionDama(FD, CD, torn);
					Returner = true;
					MoveSound();
				}

				if (esCapturableDama(FO, CO, FD, CD, torn)) //Comprueba que se pueda hacer la captura.
				{
					if (estaVacia(FD, CD)) //Hace el movimiento si entra.
					{
						setIfMensaje(false);
						Captura(FO, CO, FD, CD, torn);
						DesocuparPosicion(FO, CO);
						OcuparPosicionDama(FD, CD, torn);
						Returner = true;
					}
				}
			}
			else
			{
				setIfMensaje(true); //Avisa si el movimiento es inválido.
				desmarcaCasella(FO, CO, torn);
			}
		}
	}
	else
	{
		setIfMensaje(true); //Avisa si el movimiento es inválido.
		desmarcaCasella(FO, CO, torn);
	}
}

void Tauler::MovimientoDamaNegra(int FO, int CO, int FD, int CD, int torn, bool & Returner) {
	bool MovPositivo = (((FD == FO - 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO - 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO - 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO - 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO - 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO - 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO - 7) && ((CD == CO + 7) || (CD == CO - 7))));
	bool MovNegativo = (((FD == FO + 1) && ((CD == CO + 1) || (CD == CO - 1))) || ((FD == FO + 2) && ((CD == CO + 2) || (CD == CO - 2))) || ((FD == FO + 3) && ((CD == CO + 3) || (CD == CO - 3))) || ((FD == FO + 4) && ((CD == CO + 4) || (CD == CO - 4))) || ((FD == FO + 5) && ((CD == CO + 5) || (CD == CO - 5))) || ((FD == FO + 6) && ((CD == CO + 6) || (CD == CO - 6))) || ((FD == FO + 7) && ((CD == CO + 7) || (CD == CO - 7))));
	bool Obstaculo = false;

	if (MovPositivo || MovNegativo)
	{
		if (MovPositivo)
		{
			if (estaVacia(FD, CD))
			{
				int i = 0, j = 0;

				while ((FO - i > FD) && (CO + j < CD) && (!Obstaculo)) //Hace una comprobación en diagonal del movimiento para ver si hay alguna casilla.
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO - i][CO + j] == FITXA_BLANCA) || (T_MatrizTablero[FO - i][CO + j] == DAMA_BLANCA) || (T_MatrizTablero[FO - i][CO + j] == FITXA_NEGRA) || (T_MatrizTablero[FO - i][CO + j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				while ((FO - i > FD) && (CO - j > CD) && (!Obstaculo))
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO - i][CO - j] == FITXA_BLANCA) || (T_MatrizTablero[FO - i][CO - j] == DAMA_BLANCA) || (T_MatrizTablero[FO - i][CO - j] == FITXA_NEGRA) || (T_MatrizTablero[FO - i][CO - j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				if (!Obstaculo)
				{
					DesocuparPosicion(FO, CO);
					OcuparPosicionDama(FD, CD, torn);
					Returner = true;
					MoveSound();
				}

				if (esCapturableDama(FO, CO, FD, CD, torn)) //Comprueba que se pueda hacer la captura.
				{
					if (estaVacia(FD, CD)) //Hace el movimiento si entra.
					{
						setIfMensaje(false);
						Captura(FO, CO, FD, CD, torn);
						DesocuparPosicion(FO, CO);
						OcuparPosicionDama(FD, CD, torn);
						Returner = true;
					}
				}
			}
			else
			{
				setIfMensaje(true); //Avisa si el movimiento es inválido.
				desmarcaCasella(FO, CO, torn);
			}
		}

		if (MovNegativo)
		{
			if (estaVacia(FD, CD))
			{
				int i = 0, j = 0;

				while ((FO + i < FD) && (CO + j < CD) && (!Obstaculo)) //Hace una comprobación en diagonal del movimiento para ver si hay alguna casilla.
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO + i][CO + j] == FITXA_BLANCA) || (T_MatrizTablero[FO + i][CO + j] == DAMA_BLANCA) || (T_MatrizTablero[FO + i][CO + j] == FITXA_NEGRA) || (T_MatrizTablero[FO + i][CO + j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				while ((FO + i < FD) && (CO - j > CD) && (!Obstaculo))
				{
					i++;
					j++;

					if ((T_MatrizTablero[FO + i][CO - j] == FITXA_BLANCA) || (T_MatrizTablero[FO + i][CO - j] == DAMA_BLANCA) || (T_MatrizTablero[FO + i][CO - j] == FITXA_NEGRA) || (T_MatrizTablero[FO + i][CO - j] == DAMA_NEGRA))
					{
						setIfMensaje(true); //Avisa si el movimiento es inválido.
						desmarcaCasella(FO, CO, torn);
						Obstaculo = true;
					}
				}

				if (!Obstaculo)
				{
					DesocuparPosicion(FO, CO);
					OcuparPosicionDama(FD, CD, torn);
					Returner = true;
					MoveSound();
				}

				if (esCapturableDama(FO, CO, FD, CD, torn)) //Comprueba que se pueda hacer la captura.
				{
					if (estaVacia(FD, CD)) //Hace el movimiento si entra.
					{
						setIfMensaje(false);
						Captura(FO, CO, FD, CD, torn);
						DesocuparPosicion(FO, CO);
						OcuparPosicionDama(FD, CD, torn);
						Returner = true;
					}
				}
			}
			else
			{
				setIfMensaje(true); //Avisa si el movimiento es inválido.
				desmarcaCasella(FO, CO, torn);
			}
		}
	}
	else
	{
		setIfMensaje(true); //Avisa si el movimiento es inválido.
		desmarcaCasella(FO, CO, torn);
	}
}

void Tauler::getTablero() //Este procedimiento, al iniciar el juego, lee un fichero para detectar cuál será la matriz de partida.
{
	ifstream Fichero;
	string NombreFichero = "data/Tablero.txt";
	int i = 0, j = 0, Posicion;

	Fichero.open(NombreFichero);

	if (Fichero.is_open())
	{
		Fichero >> Posicion;

		while (!Fichero.eof())
		{
			T_MatrizTablero[i][j] = Posicion;
			T_MatrizInicial[i][j] = Posicion; //Esta segunda variable nos permitirá reiniciar el tablero al pulsar R.

			Fichero >> Posicion;

			j++;

			if (j >= 8)
			{
				i++;
				j = 0;
			}
		}
	}
}

void Tauler::getMovimientos() //Este procedimiento lee el fichero de los movimientos que deberán ejecutarse si se carga una partida.
{
	ifstream Fichero;
	string NombreFichero = "data/Movimientos.txt";
	int i = 0, Size, FO, CO, FD, CD;

	Fichero.open(NombreFichero);

	if (Fichero.is_open())
	{
		Fichero >> Size >> FO >> CO >> FD >> CD;

		Mov = new Moviment[Size];

		T_Size = Size;

		while (!Fichero.eof()) //((!Fichero.eof()) || (i < Size))
		{
			Mov[i].setFO(FO);
			Mov[i].setCO(CO);
			Mov[i].setFD(FD);
			Mov[i].setCD(CD);

			Fichero >> FO >> CO >> FD >> CD;

			i++;
		}
	}
}

int Tauler::setMovimientos(int i) //Ejecutará los movimientos que haya leído en el fichero.
{
	if (processaMoviment(Mov[i].getFO(), Mov[i].getCO(), Mov[i].getFD(), Mov[i].getCD(), T_Turno))
	{
		if (T_Turno == TORN_BLANC)
			T_Turno = TORN_NEGRE;
		else
			T_Turno = TORN_BLANC;

		for (int x = 0; x < MIDATAULER; x++)
			for (int y = 0; y < MIDATAULER; y++)
				T_MatrizInicial[x][y] = T_MatrizTablero[x][y];
	}

	return T_Turno;
}



//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//



void Tauler::newGame()
{
	//Sprites de las casillas.
	T_fons.create("data/tauler.png");
	T_cBlanca.create("data/fitxa_blanca.png");
	T_cNegra.create("data/fitxa_negra.png");
	T_cBlancaSEL.create("data/fitxa_blanca_sel.png");
	T_cNegraSEL.create("data/fitxa_negra_sel.png"); 

	//Sprites de las damas.
	T_cDamaBlanca.create("data/dama_blanca.png");
	T_cDamaNegra.create("data/dama_negra.png");
	T_cDamaBlancaSEL.create("data/dama_blanca_sel.png");
	T_cDamaNegraSEL.create("data/dama_negra_sel.png");

	//Sprites de los turnos y movimiento inválido.
	T_tBlanco.create("data/torn_blanc.png");
	T_tNegro.create("data/torn_negre.png");
	T_MovInv.create("data/avis_error.png");

	//Sprites de finalización de la partida.
	BlancasGanan.create("data/Ganan_Blancas.png");
	NegrasGanan.create("data/Ganan_Negras.png");

	//Sprites de guardado de partida.
	T_Clock1.create("data/clock.png");
	T_Clock2.create("data/clock2.png");
	T_Clock3.create("data/clock3.png");
	T_Clock4.create("data/clock4.png");

	getTablero();

	T_Turno = TORN_BLANC;
}

void Tauler::Dibuixa(int torn, bool missatge)
{
	T_fons.draw(0, 0);
	
	if (torn == TORN_BLANC) //Proceso de pintar el color del turno en el margen superior de la pantalla.
		T_tBlanco.draw(POSICIO_TORN_X, POSICIO_TORN_Y);
	else
		if(torn == TORN_NEGRE)
			T_tNegro.draw(POSICIO_TORN_X, POSICIO_TORN_Y);

	if (missatge) //Si el mensaje es true, pintar el aviso.
		T_MovInv.draw(POSICIO_AVIS_X, POSICIO_AVIS_Y);

	for (int i = 0; i < MIDATAULER; i++) //Proceso de pintar y actualizar el tablero con las fichas.
		for (int j = 0; j < MIDATAULER; j++)
		{
			if (T_MatrizTablero[i][j] == FITXA_BLANCA) //Pintar blancas.
				T_cBlanca.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
			else
				if (T_MatrizTablero[i][j] == FITXA_NEGRA) //Pintar negras.
					T_cNegra.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
				else
					if (T_MatrizTablero[i][j] == FITXA_BLANCA_SEL) //Pintar las casillas blancas seleccionadas.
						T_cBlancaSEL.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
					else
						if (T_MatrizTablero[i][j] == FITXA_NEGRA_SEL) //Pintar las casillas negras seleccionadas.
							T_cNegraSEL.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
						else
							if (T_MatrizTablero[i][j] == DAMA_BLANCA) //Pintar las damas blancas.
								T_cDamaBlanca.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
							else
								if (T_MatrizTablero[i][j] == DAMA_NEGRA) //Pintar las damas negras.
									T_cDamaNegra.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
								else
									if (T_MatrizTablero[i][j] == DAMA_BLANCA_SEL) //Pintar las damas blancas seleccionadas.
										T_cDamaBlancaSEL.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
									else
										if (T_MatrizTablero[i][j] == DAMA_NEGRA_SEL) //Pintar las damas negras seleccionadas.
											T_cDamaNegraSEL.draw(INIPANTALLAX + (j * MIDACASELLA), INIPANTALLAY + (i * MIDACASELLA));
		}

	//reset();
	//acabaPartida();
}

bool Tauler::validaClick(int x, int y, int &fila, int &columna)
{ //Transforma las coordenadas en las casillas del tablero.
	bool In = true;

	if ((x >= INIPANTALLAX) && (y >= INIPANTALLAY))
	{
		columna = (x - INIPANTALLAX) / MIDACASELLA;
		fila = (y - INIPANTALLAY) / MIDACASELLA;
		columna = columna + 1;
		fila = fila + 1;
	}
	else
	{
		columna = 0;
		fila = 0;

		In = false;
	}
	printf("Fila %d Columna %d \n", fila, columna);

	return In;
}

bool Tauler::processaMoviment(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn)
{ /*Comprueba cuál es la casilla seleccionada y el turno, luego cual es la casilla destino,
		si el movimiento es posible se realizará, en caso contrario, mostrará un mensaje de movimiento inválido.*/
	
	bool Returner = false;

	if (checkOrigenValid(FilaOrigen, ColumnaOrigen, torn)) //Comprueba si la casilla seleccionada va acorde con el jugador.
	{ 
		if (torn == TORN_BLANC) //Si el turno es el blanco realizará el movimiento.
			if (T_MatrizTablero[FilaOrigen][ColumnaOrigen] == FITXA_BLANCA_SEL)
				MovimientoCasillaBlanca(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn, Returner);
			else
				if (T_MatrizTablero[FilaOrigen][ColumnaOrigen] == DAMA_BLANCA_SEL)
					MovimientoDamaBlanca(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn, Returner);
		
		if (torn == TORN_NEGRE) //Si el turno es el negro realizará el movimiento.
			if (T_MatrizTablero[FilaOrigen][ColumnaOrigen] == FITXA_NEGRA_SEL)
				MovimientoCasillaNegra(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn, Returner);
			else
				if (T_MatrizTablero[FilaOrigen][ColumnaOrigen] == DAMA_NEGRA_SEL)
					MovimientoDamaNegra(FilaOrigen, ColumnaOrigen, FilaDesti, ColumnaDesti, torn, Returner);

		//Este if comprueba la posición de la casilla, si se puede, la transformara en dama.
		if (((FilaDesti == 0) && (T_MatrizTablero[FilaDesti][ColumnaDesti] == FITXA_BLANCA)) || 
				((FilaDesti == 7) && (T_MatrizTablero[FilaDesti][ColumnaDesti] == FITXA_NEGRA)))
			Transforma(FilaDesti, ColumnaDesti, torn);
	}

	if (Returner) //Si se quiere tener todos los movimientos, eliminar este if.
	{
		MovSavior.setFO(FilaOrigen); MovSavior.setCO(ColumnaOrigen); MovSavior.setFD(FilaDesti); MovSavior.setCD(ColumnaDesti);
		Cola.add(MovSavior);//se guarda el movimiento en la cola si este es válido.
	}

	return Returner;
}

void Tauler::marcaCasella(int fila, int columna, int torn)
{ 
	//No se hace una comprobación con el checkOrigenValid porque ya se ha realizado en el if para entrar aquí.
	if (torn == TORN_BLANC)
	{
		if (T_MatrizTablero[fila][columna] == FITXA_BLANCA)
			T_MatrizTablero[fila][columna] = FITXA_BLANCA_SEL;
		else
			if (T_MatrizTablero[fila][columna] == DAMA_BLANCA)
				T_MatrizTablero[fila][columna] = DAMA_BLANCA_SEL;
	}
	else //Cambiamos los valores a otros para reconocer la casilla marcada para poder pintarla.
		if (torn == TORN_NEGRE)
		{
			if (T_MatrizTablero[fila][columna] == FITXA_NEGRA)
				T_MatrizTablero[fila][columna] = FITXA_NEGRA_SEL;
			else
				if (T_MatrizTablero[fila][columna] == DAMA_NEGRA)
					T_MatrizTablero[fila][columna] = DAMA_NEGRA_SEL;
		}

	SelectSound();
}

void Tauler::desmarcaCasella(int fila, int columna, int torn) //Cambiamos los valores a otros para desmarcar la casilla
{
	if (torn == TORN_BLANC)
	{
		if (T_MatrizTablero[fila][columna] == FITXA_BLANCA_SEL)
			T_MatrizTablero[fila][columna] = FITXA_BLANCA;
		else
			if (T_MatrizTablero[fila][columna] == DAMA_BLANCA_SEL)
				T_MatrizTablero[fila][columna] = DAMA_BLANCA;
	}
	else 
		if (torn == TORN_NEGRE)
		{
			if (T_MatrizTablero[fila][columna] == FITXA_NEGRA_SEL)
				T_MatrizTablero[fila][columna] = FITXA_NEGRA;
			else
				if (T_MatrizTablero[fila][columna] == DAMA_NEGRA_SEL)
					T_MatrizTablero[fila][columna] = DAMA_NEGRA;
		}
}

bool Tauler::checkOrigenValid(int filaOrigen, int columnaOrigen, int torn)
{ 
	//Comprueba si la casilla escogida contiene una ficha del color del turno.
	bool Returner = false;
	bool OrigenBlanco = ((torn == TORN_BLANC) && ((T_MatrizTablero[filaOrigen][columnaOrigen] == FITXA_BLANCA) || (T_MatrizTablero[filaOrigen][columnaOrigen] == FITXA_BLANCA_SEL) || (T_MatrizTablero[filaOrigen][columnaOrigen] == DAMA_BLANCA) || (T_MatrizTablero[filaOrigen][columnaOrigen] == DAMA_BLANCA_SEL)));
	bool OrigenNegro = ((torn == TORN_NEGRE) && ((T_MatrizTablero[filaOrigen][columnaOrigen] == FITXA_NEGRA) || (T_MatrizTablero[filaOrigen][columnaOrigen] == FITXA_NEGRA_SEL) || (T_MatrizTablero[filaOrigen][columnaOrigen] == DAMA_NEGRA) || (T_MatrizTablero[filaOrigen][columnaOrigen] == DAMA_NEGRA_SEL)));

	if ((OrigenBlanco) || (OrigenNegro))
		Returner = true;
	
	return Returner;
}

int Tauler::acabaPartida()
{
	int Blancas = 0, Negras = 0;

	for (int i = 0; i < MIDATAULER; i++) //Comprueba cuantas fichas quedan de cada color
	{
		for (int j = 0; j < MIDATAULER; j++)
		{
			if ((T_MatrizTablero[i][j] == FITXA_BLANCA) || (T_MatrizTablero[i][j] == DAMA_BLANCA) || (T_MatrizTablero[i][j] == FITXA_BLANCA_SEL) || (T_MatrizTablero[i][j] == DAMA_BLANCA_SEL))
				Blancas++;

			if ((T_MatrizTablero[i][j] == FITXA_NEGRA) || (T_MatrizTablero[i][j] == DAMA_NEGRA) || (T_MatrizTablero[i][j] == FITXA_NEGRA_SEL) || (T_MatrizTablero[i][j] == DAMA_NEGRA_SEL))
				Negras++;
		}
	}

	if (Blancas == 0)
		return FITXA_BLANCA; //T_NegrasGanan.draw(0, 0);
	else
		if (Negras == 0)
			return FITXA_NEGRA; //T_BlancasGanan.draw(0, 0);
}

bool Tauler::reset()
{
	//Al pulsar la tecla R, se reinicia el tablero.

	if (Keyboard_GetKeyTrg(KEYBOARD_R))
	{
		for (int i = 0; i < MIDATAULER; i++)
		{
			for (int j = 0; j < MIDATAULER; j++)
				T_MatrizTablero[i][j] = T_MatrizInicial[i][j]; //La matriz vuelve a ser la inicial
		}

		setIfMensaje(false);
		return true;
	}
}

void Tauler::SaveGame(Screen & jocLib)
{
	ofstream Fichero;
	string NombreFichero = "data/Movimientos.txt";
	int Size = Cola.getSize();

	Fichero.open(NombreFichero);

	if (Fichero.is_open())
	{
		Fichero << Size << endl; //Escribimos el numero de movimientos que hay en la cola

		for (int i = 0; i < Size; i++) //Escribimos los movimientos guardados en la cola al fichero(en el formato correcto para luego ser leido)
		{
			Fichero << Cola.getPrimero().getFO() << " ";
			Fichero << Cola.getPrimero().getCO() << " ";
			Fichero << Cola.getPrimero().getFD() << " ";
			Fichero << Cola.getPrimero().getCD() << endl;

			Cola.take(); //Quitamos el primer elemento de la cola para continuar con el siguiente
		}

		Fichero << endl;
	}

	ClockWork(jocLib); //Pinta el símbolo de guardado. 
}

void Tauler::ClockWork(Screen & jocLib)
{
	ClockSound();

	for (int i = 0; i < 5; i++) //Dibuja el reloj de maneras distintas para crear efecto
	{
		T_Clock1.draw(0, 0);
		jocLib.update();
		Sleep(250);

		T_Clock2.draw(0, 0);
		jocLib.update();
		Sleep(250);

		T_Clock3.draw(0, 0);
		jocLib.update();
		Sleep(250);

		T_Clock4.draw(0, 0);
		jocLib.update();
		Sleep(250);
	}

	T_Clock1.draw(0, 0);
	jocLib.update();
}