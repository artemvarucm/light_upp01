#include "tablero.h"


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
	mostrarCoutSeparadorMat(N);
}

void mostrarTablero(const tTablero& tab) {
	for (int l = 0; l < tab.nFils; l++) {
		mostrarFila(tab, l, tab.nCols);
	}

}




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
	if ((x >= 0 && y >= 0) && (x < tablero.nFils && y < tablero.nCols)) {
		tablero.datos[x][y] = c;
	}
}


ifstream& tablero::operator>>(ifstream& archivo, tTablero& tab){
	archivo.open("tablero.txt");
	
	if (archivo.is_open()) {
		archivo >> tab.nFils >> tab.nCols;
		char tmp;
		for (int i = 0; i < tab.nFils; i++) {
			for (int j = 0; j < tab.nCols; j++) {
				archivo >> tmp;
				tablero::ponCeldaEnPos(tab,i, j,celda::charToCelda(tmp));
			}
		}
		int numBombillas, pos_i, pos_j;
		//tCelda celda;
		//celda::ponBombilla(celda);
		archivo >> numBombillas;
		for (int k = 0; k < numBombillas; k++) {
			archivo >> pos_i >> pos_j;
			reglasJuego::ejecutarPos(tab, pos_i, pos_j);
		}		
	}
	
	return archivo;
}

ostream& tablero::operator<<(ostream& out, const tTablero& tab) {
	mostrarCabecera(tab.nCols);
	mostrarTablero(tab);
	return out;

}

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------

bool reglasJuego::esPosQuit(int x, int y) {
	bool ok = false;
	if (x == -1 && y == 0) {
		ok = true;
	}
	return ok;
}
const int i_offsets[4] = { 0,-1,0,1 };
const int j_offsets[4] = { 1,0,-1,0 };

void apagarCeldas(tTablero& tab, int x, int y) {

	bool paradaDireccion = false;
	for (int k = 0; k < 4; k++) {
		int i = x;
		paradaDireccion = false;
		int j = y;
		while (i < tablero::getNumFilas(tab) && i >= 0 && j < tablero::getNumCols(tab) && j >= 0 && !paradaDireccion) {
			tCelda celda = tablero::celdaEnPos(tab, i, j);
			if (celda::esPared(celda)) {
				paradaDireccion = true;
			}
			else if (celda::estaIluminada(celda)) {
				celda.numBombillas--;
				tablero::ponCeldaEnPos(tab, i, j, celda);
			}
			j += j_offsets[k];
			i += i_offsets[k];
		}


	}
}

void iluminarCeldas(tTablero& tab, int x, int y) {

	bool paradaDireccion = false;
	for (int k = 0; k < 4; k++) {
		int i = x;
		paradaDireccion = false;
		//while ( && !paradaDireccion) {
		int j = y;
		while (i < tablero::getNumFilas(tab) && i >= 0 && j < tablero::getNumCols(tab) && j >= 0 && !paradaDireccion) {
			tCelda celda = tablero::celdaEnPos(tab, i, j);
			if (celda::esPared(celda)) {
				paradaDireccion = true;
			}
			else if (celda.tipo == LIBRE) {
				celda::iluminaCelda(celda);
				tablero::ponCeldaEnPos(tab, i, j, celda);
			}

			j += j_offsets[k];
			i += i_offsets[k];
		}

		//}
	}
}

void reglasJuego::ejecutarPos(tTablero& tab, int x, int y) {
	// validar no se sale tamanio
	if (!esPosQuit(x, y)) {
		tCelda celda = tablero::celdaEnPos(tab, x, y);
		if (celda::estaIluminada(celda)) {
			cout << "LA CELDA YA ESTA ILUMINADA, NO SE PUEDE PONER UNA BOMBILLA" << "\n";
		}
		else if (celda::esPared(celda)) {
			cout << "LA CELDA ES UNA PARED" << "\n";
		}
		else {
			if (celda::esBombilla(celda)) {
				celda::apagaCelda(celda);
				tablero::ponCeldaEnPos(tab, x, y, celda);
				apagarCeldas(tab, x, y);
			}
			else if (celda::estaApagada(celda)) {
				celda::ponBombilla(celda);
				tablero::ponCeldaEnPos(tab, x, y, celda);
				iluminarCeldas(tab, x, y);

			}
		}

	}

}
/*
bool reglasJuego::estaTerminado(const tTablero& juego) {

	






}

*/
