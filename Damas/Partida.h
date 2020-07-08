#include "Tauler.h"
#include <iostream>
using namespace std;

class Partida
{
public:
	Partida();
	~Partida();

	void newGame() { T.newGame(); P_Torn = TORN_BLANC; }; //Inicia todos los sprites, inicia la matriz del tablero correctamente, turno blanco
	void loadGame() { T.loadGame(); };
	void visualitza();
	void processaClick(int xMouse, int yMouse, int click);
	bool ferMoviment();
	void canviaTorn();

	int getSize() { return T.getSize(); };
	void setMovimientos(int i) { P_Torn = T.setMovimientos(i); };
	void marcaMovimiento(int i) { T.marcaMovimiento(i); };

	bool getMensaje() { return T.getIfMensaje(); };
	void setMensajeON() { T.setIfMensaje(true); };
	void setMensajeOFF() { T.setIfMensaje(false); };

	void menu(Screen & jocLib);
	void reset();
	void acabaPartida();
	void SaveGame(Screen & jocLib) { T.SaveGame(jocLib); };

private:

	Tauler T;
	int P_Torn, P_PosFilaOrigen, P_PosColumnaOrigen, P_PosFilaDestino, P_PosColumnaDestino;

};