



#include "celda.h"


const char ASTERISCO = '*', BLANCO = ' ';

char celda::celdaToChar(const tCelda& celda) {

	char resultado;

	if (celda.tipo == BOMBILLA) {
		resultado = ASTERISCO;
	}
	else if ((celda.tipo == PARED) && celda.numBombillas >= 0) {
		resultado = char(int('0') + celda.numBombillas);
	}
	else{
		resultado = BLANCO;
	}
	return resultado;

}

tCelda celda::charToCelda(char c) {
	tCelda resultado;
	if (c == 'X') {
		resultado.tipo = PARED;
		resultado.numBombillas = -1;

	}
	else if (c == '.') {
		resultado.tipo = LIBRE;
	}
	else if (c == ASTERISCO) {
		resultado.tipo = BOMBILLA;
	}
	else {
		resultado.tipo = PARED;
		resultado.numBombillas = int(c - '0');
	}
	return resultado;
}

bool celda::esPared(const tCelda& c) {

	if (c.tipo == PARED){
		return true;
	}
	else {
		return false;
	}
}

bool celda::esParedRestringida(const tCelda& c) {
	if ((c.tipo == PARED) && c.numBombillas != -1) {
		return true;
	}
	else {
		return false;
	}
}

int celda::numParedRestringida(const tCelda& c) {

	return c.numBombillas;

}

bool celda::esBombilla(const tCelda& c) {

	bool res;
	if (c.tipo == BOMBILLA) {
		res = true;
	}
	else {
		res = false;
	}
	return res;
}

bool celda::estaApagada(const tCelda& c) {
	bool res;
	if ((c.tipo = LIBRE) && (c.numBombillas == 0)) {
		res = true;
	}
	else {
		res = false;
	}
	return res;
}

bool celda::estaIluminada(const tCelda& c) {

	bool res;
	if ((c.tipo = LIBRE) && (c.numBombillas > 0)) {
		res = true;
	}
	else {
		res = false;
	}
	return res;


}

void celda::apagaCelda(tCelda& c) {

	c.tipo = LIBRE;
	c.numBombillas = 0;
}

void celda::iluminaCelda(tCelda& c) {
	c.tipo = LIBRE;
	c.numBombillas = 1;
}

void celda::ponBombilla(tCelda& c) {
	c.tipo = BOMBILLA;
}

