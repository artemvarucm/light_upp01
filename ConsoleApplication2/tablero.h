#include "celda.h"
#include <fstream>

const int MAX_FILS = 10;
const int MAX_COLS = 10;
typedef tCelda tTableroDatos[MAX_FILS][MAX_COLS];
typedef struct {
	int nFils, nCols;
	tTableroDatos datos;
} tTablero;

namespace tablero {
	int getNumFilas(const tTablero& tab);
	int getNumCols(const tTablero& tab);
	tCelda celdaEnPos(const tTablero& tablero, int x, int y);
	void ponCeldaEnPos(tTablero& tablero, int x, int y, const tCelda& c);
	ostream& operator<<(ostream& out, const tTablero& tab);
	ifstream& operator>>(ifstream& archivo, tTablero& tab)
}