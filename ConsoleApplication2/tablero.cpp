#include "tablero.h"

using namespace tablero;

int getNumFilas(const tTablero& tab) {
	return tab.nFils;
}

int getNumCols(const tTablero& tab) {
	return tab.nCols;
}

tCelda celdaEnPos(const tTablero& tablero, int x, int y) {
	return tablero.datos[x][y];
}

void ponCeldaEnPos(tTablero& tablero, int x, int y, const tCelda& c) {
	tablero.datos[x][y] = c;
}

ostream& operator<<(ostream& out, const tTablero& tab) {

}

ifstream& operator>>(ifstream& archivo, tTablero& tab) {
	archivo >> tab.nFils >> tab.nCols;
	for (int i = 0; i < nFils; i++) {
		for (int j = 0; j < nCols; j++){
			//cargar tablero
		}
	}
}
