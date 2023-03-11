#include "celda.h"

char celda::celdaToChar(const tCelda& celda) {
	char c = resto;
	if (celda.tipo == BOMBILLA) {
		c = bombillaChar;
	}
	else if (celda.tipo == PARED && celda.numBombillas >= 0) {
			c = char(int('0') + celda.numBombillas);
	}
	return c;
}

tCelda celda::charToCelda(char c) {
	tCelda celda;
	celda.numBombillas = 0;
	switch (c) {
		case paredChar: {
			celda = C_PARED;
			celda.numBombillas = -1;
			}
			break;
		case libreChar:
			celda.tipo = LIBRE;
			break;
		case bombillaChar:
			celda.tipo = BOMBILLA;
			break;
		default:
			// validar si es int
			celda.tipo = PARED;
			celda.numBombillas = int(c - '0');
	}
	return celda;

}
bool celda::esPared(const tCelda& c) {
	return c.tipo == PARED;
}
int celda::numParedRestringida(const tCelda& c) {
	// CAMBIAR
	return c.numBombillas;
}
bool celda::esParedRestringida(const tCelda& c) {
	return c.tipo == PARED && c.numBombillas >=0;
}

bool celda::esBombilla(const tCelda& c) {
	return c.tipo == BOMBILLA;
}
bool celda::estaApagada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas == 0;
}
bool celda::estaIluminada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas >= 0;
}
void celda::apagaCelda(tCelda& c) {
	c.tipo = LIBRE;
	c.numBombillas = 0;
}
void celda::iluminaCelda(tCelda& c) {
	// CAMBIAR
	c.tipo = LIBRE;
	c.numBombillas = 1;
}
void celda::ponBombilla(tCelda& c) {
	c.tipo = BOMBILLA;
}
