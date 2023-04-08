#include "tablero.h"
#include "reglasJuego.h"

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

const int HUECOS = 2;
const int N = 5;

void mostrarCoutSeparadorMat(int N) {
	cout << "\t -+";
	for (int col = 0; col < N; ++col) {
		cout << setw(HUECOS + 2) << setfill('-') << '+' << setfill(' ');
	}
	cout << endl;
}

void mostrarCabecera(int N) {
	// muestra los numeros de columna
	cout << WHITE << "\t  |";
	for (int col = 0; col < N; ++col) {
		cout << LBLUE << setw(HUECOS) << col << " " << RESET << '|';
	}
	cout << endl;

	// muestra la linea separadora 
	mostrarCoutSeparadorMat(N);
}

void mostrarFila(const tTablero& tab, int i, int N) {

	//muestra una fila donde todas las celdas son bombillas 
	cout << "\t" << LBLUE << setw(HUECOS) << i << RESET << '|';
	for (int c = 0; c < N; c++) {
		char cel;
		tCelda celda = tablero::celdaEnPos(tab, i, c);
		if ((celda.tipo == BOMBILLA) || (celda.tipo == LIBRE && celda.numBombillas > 0 && celda.numBombillas < 5)) {
			cout << BG_YELLOW << BLACK;
		}
		else if ((celda.tipo == LIBRE) && (celda.numBombillas <= 0 || celda.numBombillas >= 5)) {
			cout << BG_WHITE;
		}
		else if ((celda.tipo == PARED) && (celda.numBombillas >= 0 && celda.numBombillas < 5)) {
			cout << BG_BLACK << WHITE;
		}
		else {
			cout << BG_BLACK;
		}

		cel = celda::celdaToChar(celda);
		cout << setw(HUECOS) << setfill(' ') << cel << " " << RESET;
		cout << '|';
	}
	cout << endl;

	// muestra la linea separadora 
	mostrarCoutSeparadorMat(N);
}

void mostrarTablero(const tTablero& tab) {
	for (int l = 0; l < tab.nFils; l++) {
		mostrarFila(tab, l, tab.nCols);
	}

}

ostream& tablero::operator<<(ostream& out, const tTablero& tab) {
	/*
	* Sobrecarga del operador << para mostrar el tablero
	*/
	mostrarCabecera(tab.nCols);
	mostrarTablero(tab);
	return out;

}

ifstream& tablero::operator>>(ifstream& archivo, tTablero& tab) {
	/*
	* Sobrecarga del extractor >> para cargar el tablero
	*/
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
		// Reutilizamos funcion, que ya esta definida en el modulo reglasJuego
		reglasJuego::ejecutarPos(tab, x, y);
	}
	return archivo;
}
