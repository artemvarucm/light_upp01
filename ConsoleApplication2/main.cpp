#include "reglasJuego.h"
#include <fstream>
using namespace tablero;

int main() {
	tTablero tablero;
	/*tablero.nFils = 3;
	tablero.nCols = 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tCelda celda = {PARED, 3};
			tablero.datos[i][j] = celda;
		}
	}*/
	ifstream archivo;
	archivo.open("./tableros.txt");
	if (archivo.is_open()) {
		archivo >> tablero;
		archivo.close();
	}
	reglasJuego::ejecutarPos(tablero, 1, 1);
	cout << tablero;
	return 0;
}
