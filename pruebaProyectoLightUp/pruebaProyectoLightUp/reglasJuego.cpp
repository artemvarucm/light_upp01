#include "reglasJuego.h"
#include "tablero.h"

const int I_OFFSETS[4] = { 0,-1,0,1 };
const int J_OFFSETS[4] = { 1,0,-1,0 };

bool reglasJuego::esPosQuit(int x, int y) {
	// Devuelve true si la posicion introducida coincide 
	// la posicion logica para salir (-1, 0)
	bool ok = false;
	if (x == -1 && y == 0) {
		ok = true;
	}
	 
	return ok;
}

bool reglasJuego::esPosReset(int x, int y) {
	bool ok = false;
	if (x == -1 && y == -1) {
		ok = true;
	}
	return ok;

}

void apagarCeldas(tTablero& tab, int x, int y) {
	// Baja el nivel de iluminacion restando 1 al numero de bombillas 
	// a las celdas correspondientes en forma de cruz
	// a partir de la posicion (x, y) que es donde se quita la bombilla

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
			j += J_OFFSETS[k];
			i += I_OFFSETS[k];
		}
	}
}

void iluminarCeldas(tTablero& tab, int x, int y) {
	// Ilumina las celdas correspondientes en forma de cruz
	// a partir de la posicion (x, y) que es donde se pone la bombilla
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

			j += J_OFFSETS[k];
			i += I_OFFSETS[k];
		}
	}
}

bool validarPosicion(const tTablero& tab, int x, int y) {
	// Devuelve true si la posicion cae dentro del rango del tablero
	return (
		x >= 0 && x < tablero::getNumFilas(tab) 
		&& 
		y >= 0 && y < tablero::getNumCols(tab)
	);
}

void reglasJuego::ejecutarPos(tTablero& tab, int x, int y) {
	// Pone o quita una bombilla dependiendo del estado de la celda en posicion (x, y)
	if (validarPosicion(tab, x, y)) {
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
		else if (celda::estaIluminada(celda)) {
			cout << "\n";
			cout << "No se puede colocar una bombilla en esa posicion porque ya esta iluminada." << "\n";
			cout << "Prueba a quitar antes la bombilla que esta iluminando esa casilla." << "\n";
			cout << "\n";
		}
	} else {
		cout << "\n";
		cout << "Posicion no valida (x entre [0, " << tablero::getNumFilas(tab) - 1 << "]; "; 
		cout << "y entre [0, " << tablero::getNumCols(tab) - 1 << "]\n";
		cout << "\n";
	}
}

int comprobarParedRestringida(const tTablero& tab, int x, int y) {
	// Calculamos el numero de bombillas alrededor de una pared restringida
	// para despues compararlo con el numero de bombillas necesarias (y suficientes) 
	int cont = 0;
	for (int k = 0; k < 4; k++) {
		int i = x + I_OFFSETS[k];
		int j = y + J_OFFSETS[k];

		if ((tablero::celdaEnPos(tab, i, j).tipo == BOMBILLA) && i >= 0 && i < tablero::getNumFilas(tab) && j >= 0 && j < tablero::getNumCols(tab)) {
			cont++;
		}
	}
	return cont;
}


bool reglasJuego::estaTerminado(tTablero const& juego) {
	// Revisamos si se ha terminado el juego segun las reglas definidas 
	int x = 0;
	int y = 0;
	bool ok = true;
	tCelda celda;
	while (x < tablero::getNumFilas(juego) && ok) {
		y = 0;
		while (y < tablero::getNumCols(juego) && ok) {
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



void reglasJuego::resetTablero(tTablero& tab) {
	tCelda celda;
	for (int i = 0; i < tablero::getNumFilas(tab); i++) {
		for (int j = 0; j < tablero::getNumCols(tab); j++) {
			celda = tablero::celdaEnPos(tab, i, j);
			if (!celda::esPared(celda)) {
				celda::apagaCelda(celda);
				tablero::ponCeldaEnPos(tab, i, j, celda);
			}
		}
	}
	
}
