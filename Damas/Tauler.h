#include "Joc.h"
#include "lib/libreria.h"
#include <fstream>
#include "Moviment.h"
#include "Cola.h"
#include <Windows.h>
using namespace std;

const int MIDATAULER = 8;

//========================================================================
// Mida Pantalla
const int MIDAX = 624;
const int MIDAY = 680;

//========================================================================
// Inici del taulell respecte la cantonada superior esquerre
const int INIPANTALLAX = 0;
const int INIPANTALLAY = 56;

//========================================================================
// Fi del taulell respecte la cantonada inferior dreta
const int FIPANTALLAX = 624;
const int FIPANTALLAY = 680;

// Tamany d'una casella del tauler
const int MIDACASELLA = 78;

// Coordenades de pantalla on mostrar el jugador del torn actual
const int POSICIO_TORN_X = 120;
const int POSICIO_TORN_Y = 10;

// Coordenades de pantalla on mostrar el missatge d'av�s de moviment invalid
const int POSICIO_AVIS_X = 250;
const int POSICIO_AVIS_Y = 10;

// Constants per especificar el jugador del torn actual
const int TORN_BLANC = 1;
const int TORN_NEGRE = 2;

// Constants per codificar el tipus de fitxa que hi ha a cada posicio del tauler
const int FITXA_BLANCA = 1;
const int FITXA_NEGRA = 2;
const int FITXA_BLANCA_SEL = 11;
const int FITXA_NEGRA_SEL = 22;
const int DAMA_BLANCA = 111;
const int DAMA_NEGRA = 222;
const int DAMA_BLANCA_SEL = 1111;
const int DAMA_NEGRA_SEL = 2222;
const int BUIT = 0;

class Tauler
{
public:
	Tauler();
	~Tauler();

	bool estaVacia(int PosicionI, int PosicionJ);
	void DesocuparPosicion(int PosicionI, int PosicionJ); //int(&Matrix)[MIDATAULER][MIDATAULER], 
	void OcuparPosicion(int PosicionI, int PosicionJ, int turno); //int(&Matrix)[MIDATAULER][MIDATAULER],
	void OcuparPosicionDama(int PosicionI, int PosicionJ, int turno);
	void setIfMensaje(bool Mensaje);
	bool getIfMensaje() { return T_Mensaje; };

	//Funciones de movimiento.
	bool MOV_BLANC(int FO, int CO, int FD, int CD) { return ((FD == FO - 1) && ((CD == CO + 1) || (CD == CO - 1))); }; //Booleano que comprueba si la casilla destino BLANCA es posible
	bool MOV_NEGRE(int FO, int CO, int FD, int CD) { return ((FD == FO + 1) && ((CD == CO + 1) || (CD == CO - 1))); }; //Booleano que comprueba si la casilla destino NEGRA es posible
	
	bool esCapturable(int FO, int CO, int FD, int CD, int turno);
	bool esCapturableDama(int FO, int CO, int FD, int CD, int turno);
	void Captura(int FO, int CO, int FD, int CD, int turno);
	void Transforma(int PosicionI, int Posicionj, int turno);
	
	void MovimientoCasillaBlanca(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner);
	void MovimientoCasillaNegra(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner);
	void MovimientoDamaBlanca(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner);
	void MovimientoDamaNegra(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn, bool &Returner);

	void getTablero();//obtiene el tablero inicial desde un fichero
	void getMovimientos();//obtiene los movimientos de un fichero
	int setMovimientos(int i);
	void marcaMovimiento(int i) { marcaCasella(Mov[i].getFO(), Mov[i].getCO(), T_Turno); };
	int getSize() { return T_Size; };

	void newGame();
	void loadGame() { getMovimientos(); };

	void Dibuixa(int torn, bool missatge);
	bool validaClick(int x, int y, int &fila, int &columna);
	bool processaMoviment(int FilaOrigen, int ColumnaOrigen, int FilaDesti, int ColumnaDesti, int torn);
	void marcaCasella(int fila, int columna, int torn);
	void desmarcaCasella(int fila, int columna, int torn);
	bool checkOrigenValid(int filaOrigen, int columnaOrigen, int torn);

	int acabaPartida();
	bool reset();
	void SaveGame(Screen & jocLib);
	void ClockWork(Screen & jocLib);

	//Sonidos
	void SelectSound() { PlaySound(TEXT("data/Select.wav"), NULL, SND_ASYNC); };
	void MoveSound() { PlaySound(TEXT("data/Move.wav"), NULL, SND_ASYNC); };
	void PopSound() { PlaySound(TEXT("data/Pop.wav"), NULL, SND_ASYNC); };
	void ErrorSound() { PlaySound(TEXT("data/Error.wav"), NULL, SND_ASYNC); };
	void TransformationSound() { PlaySound(TEXT("data/Transformation.wav"), NULL, SND_ASYNC); };
	void WinSound() { PlaySound(TEXT("data/Win.wav"), NULL, SND_ASYNC); };
	void ClockSound() { PlaySound(TEXT("data/Clock.wav"), NULL, SND_ASYNC); };

	Sprite BlancasGanan, NegrasGanan;

private:
	
	int T_MatrizTablero[MIDATAULER][MIDATAULER];
	int T_MatrizInicial[MIDATAULER][MIDATAULER];
	int T_Turno, T_Size;
	bool T_Mensaje = false;

	Moviment * Mov, MovSavior;

	Sprite T_fons;
	Sprite T_cBlanca, T_cNegra;
	Sprite T_cBlancaSEL, T_cNegraSEL;
	Sprite T_cDamaBlanca, T_cDamaNegra;
	Sprite T_cDamaBlancaSEL, T_cDamaNegraSEL;
	Sprite T_tBlanco, T_tNegro, T_MovInv;
	Sprite T_Clock1, T_Clock2, T_Clock3, T_Clock4;

	Cola Cola;
	
};