/*
1ºD 
Grado Ingeniería de Datos e Inteligencia Artificial

DANIEL COLETO QUEREDA
ARTEM VARTANOV
*/
#include "reglasJuego.h"
#include "listaTableros.h"
#include <fstream>

using namespace tablero;
//const string FILENAME = "tablero.txt";
int main() {
	
	cout << WHITE << "\n" << "\n" << "\t" << "     " << "JUEGO LIGHT-UP" << "\n" << "\n";
	tListaTableros tableros;
	ifstream archivo;
	listaTableros::inicializaVectorTablero(tableros);
	cout << WHITE << "Introduce el archivo para cargar partida: ";
	string FILENAME;
	getline(cin, FILENAME);
	
	archivo.open(FILENAME);
	if (archivo.is_open()) {
		listaTableros::operator>>(archivo, tableros);
		archivo.close();

		
		listaTableros::operator<<(cout, tableros);
/*
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
		}*/
	} else {
		cout << "Archivo no se pudo abrir. Revise si el nombre del archivo esta escrito correctamente\n";
	}

	return 0;
