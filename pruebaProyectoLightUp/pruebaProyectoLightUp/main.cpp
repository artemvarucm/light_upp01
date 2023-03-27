
#include "reglasJuego.h"
#include <fstream>
	using namespace tablero;

	int main() {

		tTablero tablero;

		ifstream archivo;
		archivo.open("./tablero.txt");
		if (archivo.is_open()) {
			archivo >> tablero;
			archivo.close();
		}
		cout << WHITE << "\n" << "\n" << "\t" << "     " << "JUEGO LIGHT-UP" << "\n" << "\n";

		cout << tablero;

		int contadorJuego = 0;
		bool bien = true;
		
		while (!reglasJuego::estaTerminado(tablero) && bien) {
			int x;
			int y;
			cout << WHITE << "INTODUCE DONDE QUIERES COLOCAR/QUITAR UNA BOMBILLA" << "\n";


			cout << WHITE << "Posicion x: ";
			cin >> x;
			cout << WHITE << "Posicion y: ";
			cin >> y;

			if (!reglasJuego::esPosQuit(x, y)) {

				reglasJuego::ejecutarPos(tablero, x, y);
				cout << tablero;
				contadorJuego++;
				cout << "Contador: " << contadorJuego << "\n";



			}
			else {
				bien = false;
				cout << WHITE << "El juego ha acabado, has decidido abandonar." << "\n";
			}


			cout << "\n";



		}
		if (reglasJuego::estaTerminado(tablero)) {
			cout << WHITE << "HAS GANADO!!!" << "\n";
			cout << WHITE << "Has terminado el juego en " << contadorJuego << " movimientos" << "\n";
		}



		return 0;
	}
