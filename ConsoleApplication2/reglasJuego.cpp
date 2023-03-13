#include "reglasJuego.h"


bool reglasJuego::esPosQuit(int x, int y) {
	bool ok = true;;
	if (x == -1 && y == 0) {
		ok = false;
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
		while (i < tablero::getNumFilas(tab) && i >=0 && !paradaDireccion) {
			int j = y;
			while (j < tablero::getNumCols(tab) && j >= 0 && !paradaDireccion) {
				tCelda celda = tablero::celdaEnPos(tab, x, y);
				if (celda::esPared(celda)) {
					paradaDireccion = true;
				}
				else if (celda::estaIluminada(celda)) {
						celda.numBombillas--;
						tablero::ponCeldaEnPos(tab, x, y, celda);
				}
				j += j_offsets[k];
			}
			i += i_offsets[k];
		}
	}
}

void iluminarCeldas(tTablero& tab, int x, int y) {

	bool paradaDireccion = false;
	for (int k = 0; k < 4; k++) {
		int i = x;
		paradaDireccion = false;
		while (i < tablero::getNumFilas(tab) && i >= 0 && !paradaDireccion) {
			int j = y;
			while (j < tablero::getNumCols(tab) && j >= 0 && !paradaDireccion) {
				tCelda celda = tablero::celdaEnPos(tab, x, y);
				if (celda::esPared(celda)) {					
					paradaDireccion = true;
				}
				else {
					celda::iluminaCelda(celda);
				}
				
				j += j_offsets[k];
			}
			i += i_offsets[k];
		}
	}
}

void reglasJuego::ejecutarPos(tTablero& tab, int x, int y) {
	if (!esPosQuit(x, y)) {
		tCelda celda = tablero::celdaEnPos(tab, x, y);
		if (celda::esBombilla(celda)) {
			celda::apagaCelda(celda);
			apagarCeldas(tab, x, y);
		}
		else if (celda::estaApagada(celda)) {
			celda::ponBombilla(celda);
			iluminarCeldas(tab, x, y);
		}
		
	}
	
}

