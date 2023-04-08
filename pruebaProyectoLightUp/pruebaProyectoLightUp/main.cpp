/*
1ºD 
Grado Ingeniería de Datos e Inteligencia Artificial

DANIEL COLETO QUEREDA 
ARTEM VARTANOV
*/
#include "reglasJuego.h"
#include <fstream>
using namespace tablero;

int main() {
	
	cout << WHITE << "\n" << "\n" << "\t" << "     " << "JUEGO LIGHT-UP" << "\n" << "\n";
	tTablero tablero;
	ifstream archivo;

	cout << WHITE << "Introduce el archivo para cargar partida: ";
	string filename;
	getline(cin, filename);
	archivo.open(filename);
	if (archivo.is_open()) {
		archivo >> tablero;
		archivo.close();

		cout << tablero;

		int contadorJuego = 0;
		bool bien = true;
		// Ciclo de vida del juego
		while (!reglasJuego::estaTerminado(tablero) && bien) {
			int x;
			int y;
			cout << WHITE << "INTODUCE DONDE QUIERES COLOCAR/QUITAR UNA BOMBILLA" << "\n";
			cout << WHITE << "Posicion x: ";
			cin >> x;
			cout << WHITE << "Posicion y: ";
			cin >> y;
			if (!reglasJuego::esPosQuit(x, y)) {
				// El jugador quiere continuar el juego
				reglasJuego::ejecutarPos(tablero, x, y);
				cout << tablero;
				contadorJuego++;
				cout << "Contador: " << contadorJuego << "\n";
			} else {
				bien = false;
				cout << WHITE << "El juego ha acabado, has decidido abandonar." << "\n";
			}
			cout << "\n";
		}
		if (reglasJuego::estaTerminado(tablero)) {
			cout << WHITE << "HAS GANADO!!!" << "\n";
			cout << WHITE << "Has terminado el juego en " << contadorJuego << " movimientos" << "\n";
		}
	} else {
		cout << "Archivo no se pudo abrir. Revise si el nombre del archivo esta escrito correctamente\n";
	}

	return 0;
}
