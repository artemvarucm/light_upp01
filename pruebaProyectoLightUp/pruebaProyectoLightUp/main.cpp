
#include "tablero.h"
using namespace std;




int main() {

	tTablero tablero;

	ifstream archivo;
	tablero::operator>>(archivo, tablero);	

	int i, j;
	cout << BLUE<<"DONDE QUIERES PONER UNA BOMBILLA: " << "\n";

	cin >> i >> j;
	reglasJuego::ejecutarPos(tablero, i, j);
		 
		/*reglasJuego::ejecutarPos(tablero, 0, 0);
		reglasJuego::ejecutarPos(tablero, 0, 2);
		reglasJuego::ejecutarPos(tablero, 0, 4);
		reglasJuego::ejecutarPos(tablero, 1, 3);
		reglasJuego::ejecutarPos(tablero, 2, 0);
		reglasJuego::ejecutarPos(tablero, 3, 1);
		reglasJuego::ejecutarPos(tablero, 4, 3);*/
	tablero::operator<<(cout,tablero);
	
	
	
	return 0;
}
