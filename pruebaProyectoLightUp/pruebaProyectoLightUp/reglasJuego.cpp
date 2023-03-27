#include "reglasJuego.h"
#include "tablero.h"

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
		while (
			i < tablero::getNumFilas(tab) &&
			i >= 0 &&
			j < tablero::getNumCols(tab) &&
			j >= 0 &&
			!paradaDireccion) {
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
		int j = y;
		while (
			i < tablero::getNumFilas(tab) &&
			i >= 0 &&
			j < tablero::getNumCols(tab) &&
			j >= 0 &&
			!paradaDireccion
			) {
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
	}
}

void reglasJuego::ejecutarPos(tTablero& tab, int x, int y) {
	// validar no se sale tamanio
	if (!esPosQuit(x, y)) {
		tCelda celda = tablero::celdaEnPos(tab, x, y);
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


int comprobarParedRestringida(const tTablero& tab, int x, int y) {
	int cont = 0;
	for (int k = 0; k < 4; k++) {
		int i = x + i_offsets[k];
		int j = y + j_offsets[k];

		if ((tab.datos[i][j].tipo == BOMBILLA) && i >= 0 && i < tab.nFils && j >= 0 && j < tab.nCols) {
			cont++;
		}

	}
	return cont;
}


bool reglasJuego::estaTerminado(tTablero const& juego) {
	int x = 0;
	int y = 0;
	bool ok = true;
	tCelda celda;
	while (x < juego.nFils && ok) {

		while (y < juego.nCols && ok) {

			celda = tablero::celdaEnPos(juego, x, y);
			if (celda::esParedRestringida(celda) && (celda::numParedRestringida(celda) != comprobarParedRestringida(juego,x,y))) {
				ok = false;
			}
			else if (!celda::esPared(celda) && (!celda::esBombilla(celda) && !celda::estaIluminada(celda))) {
				ok = false;
			}
			y++;
		}

		x++;
	}
	
	return ok;


}


