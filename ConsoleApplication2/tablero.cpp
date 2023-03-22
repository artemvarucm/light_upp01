#include "tablero.h"
#include "colors.h"
#include "reglasJuego.h"
// cambiar los includes

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
	if (x >= 0 && y >= 0 && x < tablero.nFils && y < tablero.nCols ){
		tablero.datos[x][y] = c;
	}
}

// FIX
const int HUECO = 2;

void mostrarHeader(const tTablero& tab) {
	cout << "\t  ";
	for (int col = 0; col < tab.nCols; ++col) {
		cout << "|" << setw(HUECO + 1) << setfill(' ') << col;
		cout << setw(HUECO + 1) << setfill(' ');
	}
	cout << "|";
	cout << endl;
}

void mostrarCoutSeparadorMat(const tTablero& tab) {
	cout << "\t -+";
	for (int col = 0; col < tab.nCols; ++col) {
		cout << setw(HUECO*2 + 2) << setfill('-') << '+';
	}
	cout << endl;
}

void mostrarFila(int i, const tTablero& tab) {
	cout << "\t " << i;
	for (int col = 0; col < tab.nCols; ++col) {
		cout << RESET << "|";
		
		tCelda celda = tablero::celdaEnPos(tab, i, col);
		if (celda.tipo == BOMBILLA || (celda.tipo == LIBRE && celda.numBombillas > 0)) {
			cout << BG_YELLOW;
		} else if (celda.tipo == LIBRE) {
			cout << BG_WHITE;
		}
	    cout << setw(HUECO + 1) << setfill(' ');
		cout << celda::celdaToChar(celda);
		cout << setw(HUECO + 4) << setfill(' ');
	}
	cout << RESET << "|";
	cout << endl;
	mostrarCoutSeparadorMat(tab);
}

ostream& tablero::operator<<(ostream& out, const tTablero& tab) {
	mostrarHeader(tab);
	mostrarCoutSeparadorMat(tab);
	for (int i = 0; i < tab.nFils; i++) {
		mostrarFila(i, tab);
	}
	return out;
}

ifstream& tablero::operator>>(ifstream& archivo, tTablero& tab) {
	archivo >> tab.nFils >> tab.nCols;
	for (int i = 0; i < tab.nFils; i++) {
		for (int j = 0; j < tab.nCols; j++){
			char c;
			archivo >> c;
			ponCeldaEnPos(tab, i, j, celda::charToCelda(c));
		}
	}

	int nBombillas;
	archivo >> nBombillas;
	for (int i = 0; i < nBombillas; i++) {
		tCelda celda;
		int x, y;
		archivo >> x >> y;
		//celda::ponBombilla(celda);
		reglasJuego::ejecutarPos(tab, x, y);
		//tablero::ponCeldaEnPos(tab, x, y, celda);
	}
	return archivo;
}