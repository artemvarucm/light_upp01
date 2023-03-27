#include "tablero.h"

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
	if (x >= 0 && y >= 0 && x < tablero.nFils && y < tablero.nCols) {
		tablero.datos[x][y] = c;
	}
}

// FIX
const int HUECOS = 2;

void mostrarCoutSeparadorMat(const tTablero& tab) {
	cout << "\t -+";
	for (int col = 0; col < tab.nCols; ++col) {
		cout << setw(HUECOS + 2) << setfill('-') << '+' << setfill(' ');
	}
	cout << endl;
}

void mostrarCabecera(const tTablero& tab) {
	// muestra los numeros de columna
	cout << WHITE << "\t  |";
	for (int col = 0; col < tab.nCols; ++col) {
		cout << LBLUE << setw(HUECOS) << col << " " << RESET << '|';
	}
	cout << endl;

	// muestra la linea separadora 
	mostrarCoutSeparadorMat(tab);
}

void mostrarFila(const tTablero& tab, int i) {

	//muestra una fila donde todas las celdas son bombillas 
	cout << "\t" << LBLUE << setw(HUECOS) << i << RESET << '|';
	for (int c = 0; c < tab.nCols; c++) {
		char cel;
		if ((tab.datos[i][c].tipo == BOMBILLA) || (tab.datos[i][c].tipo == LIBRE && tab.datos[i][c].numBombillas > 0 && tab.datos[i][c].numBombillas < 5)) {
			cout << BG_YELLOW << BLACK;
		}
		else if ((tab.datos[i][c].tipo == LIBRE) && (tab.datos[i][c].numBombillas <= 0 || tab.datos[i][c].numBombillas >= 5)) {
			cout << BG_WHITE;
		}
		else if ((tab.datos[i][c].tipo == PARED) && (tab.datos[i][c].numBombillas >= 0 && tab.datos[i][c].numBombillas < 5)) {
			cout << BG_BLACK << WHITE;
		}
		else {
			cout << BG_BLACK;
		}

		cel = celda::celdaToChar(tab.datos[i][c]);
		cout << setw(HUECOS) << setfill(' ') << cel << " " << RESET;
		cout << '|';
	}
	cout << endl;

	// muestra la linea separadora 
	mostrarCoutSeparadorMat(tab);
}

void mostrarTablero(const tTablero& tab) {
	for (int l = 0; l < tab.nFils; l++) {
		mostrarFila(tab, l);
	}

}

ostream& tablero::operator<<(ostream& out, const tTablero& tab) {
	mostrarCabecera(tab);
	mostrarTablero(tab);
	return out;

}

ifstream& tablero::operator>>(ifstream& archivo, tTablero& tab) {
	archivo >> tab.nFils >> tab.nCols;
	for (int i = 0; i < tab.nFils; i++) {
		for (int j = 0; j < tab.nCols; j++) {
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
