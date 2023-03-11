#include "tablero.h"


int tablero::getNumFilas(const tTablero& tab) {
	return tab.nFils;
}
int tablero::getNumCols(const tTablero& tab) {
	return tab.nCols;
}

tCelda tablero::celdaEnPos(const tTablero& tablero, int x, int y) {
	return tablero.datos[x][y];
}

void tablero::ponCeldaEnPos(tTablero& tablero, int x, int y, const tCelda& c) {
	if ((x >= 0 && y >= 0) && (x < tablero.nFils && y < tablero.nCols )){
		tablero.datos[x][y] = c;
	}
}
