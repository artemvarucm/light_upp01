#include "reglasJuego.h"
#include <fstream>
using namespace tablero;

int main() {

	tTablero tablero;
	
	ifstream archivo;
	archivo.open("./tableros.txt");
	if (archivo.is_open()) {
		archivo >> tablero;
		archivo.close();
	}

	int i, j;
	cout << BLUE << "DONDE QUIERES PONER UNA BOMBILLA: " << "\n";

	cin >> i >> j;
	reglasJuego::ejecutarPos(tablero, i, j);
	/*reglasJuego::ejecutarPos(tablero, 0, 0);
		reglasJuego::ejecutarPos(tablero, 0, 2);
		reglasJuego::ejecutarPos(tablero, 0, 4);
		reglasJuego::ejecutarPos(tablero, 1, 3);
		reglasJuego::ejecutarPos(tablero, 2, 0);
		reglasJuego::ejecutarPos(tablero, 3, 1);
		reglasJuego::ejecutarPos(tablero, 4, 3);*/
	cout << tablero;
	return 0;
}
