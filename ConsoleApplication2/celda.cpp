#include "celda.h"


char celda::celdaToChar(const tCelda& celda) {
	char c = resto;
	if (celda.tipo == tTipo::BOMBILLA) {
		c = bombillaChar;
	}
	else if (celda.tipo == tTipo::PARED && celda.numBombillas >= 0) {
			c = celda.numBombillas;
	}
}

tCelda celda::charToCelda(char c) {
	tCelda celda;
	switch (c) {
		case paredChar: {
			celda = C_PARED;
			}
			break;
		case libreChar:
			celda.tipo = tTipo::LIBRE;
			break;
		case bombillaChar:
			celda.tipo = tTipo::BOMBILLA;
			break;
		default:
			// validar si es int
			celda.tipo = tTipo::PARED;
			celda.numBombillas = int(c - '0');
	}
	return celda;

}
bool celda::esPared(const tCelda& c) {
	return c.tipo == tTipo::PARED;
}
int celda::numParedRestringida(const tCelda& c) {
	// CAMBIAR
	return c.numBombillas;
}
bool celda::esParedRestringida(const tCelda& c) {
	return c.tipo == tTipo::PARED && c.numBombillas >=0;
}

bool celda::esBombilla(const tCelda& c) {
	return c.tipo == tTipo::BOMBILLA;
}
bool celda::estaApagada(const tCelda& c) {
	return c.tipo == tTipo::LIBRE && c.numBombillas == 0;
}
bool celda::estaIluminada(const tCelda& c) {
	return c.tipo == tTipo::LIBRE && c.numBombillas >= 0;
}
void celda::apagaCelda(tCelda& c) {
	c.tipo = tTipo::LIBRE;
	c.numBombillas = 0;
}
void celda::iluminaCelda(tCelda& c) {
	// CAMBIAR
	c.tipo = tTipo::LIBRE;
	c.numBombillas = 1;
}
void celda::ponBombilla(tCelda& c) {
	c.tipo = tTipo::BOMBILLA;
}
