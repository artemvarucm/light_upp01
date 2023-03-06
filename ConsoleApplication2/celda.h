#ifndef CELDAH
#define CELDAH

typedef enum tTipo { PARED, BOMBILLA, LIBRE };
typedef struct {
	tTipo tipo;
	int numBombillas;
} tCelda;

namespace celda {
	const tCelda C_PARED = { tTipo::PARED, -1 };
	const char bombillaChar = '*';
	const char paredChar = 'X';
	const char libreChar = '.';
	const char resto = ' ';
	char celdaToChar(const tCelda& celda);
	tCelda charToCelda(char c);
	bool esPared(const tCelda& c);
	int numParedRestringida(const tCelda& c);
	bool esParedRestringida(const tCelda& c);
	bool esBombilla(const tCelda& c);
	bool estaApagada(const tCelda& c);
	bool estaIluminada(const tCelda& c);
	void apagaCelda(tCelda& c);
	void iluminaCelda(tCelda& c);
	void ponBombilla(tCelda& c);
}

#endif