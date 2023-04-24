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

void jugar(tTablero& juego, int x, int y, int& nIt);


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
		int niv, posNivel;
		tPtrTablero ptrTab = NULL;
		tTablero tablero;
		while (ptrTab == NULL){
			cout << "\nELIGE EL NIVEL: ";
			cin >> niv;
			ptrTab = listaTableros::dameTableroNivel(tableros, niv, posNivel);
			
			if(ptrTab == NULL) {
				cout << "No existe nivel deseado. Empiece desde el primer nivel disponible" << "\n";
			}
		}
		bool salir = false;
		while (posNivel < tableros.nElem && !salir && ptrTab != NULL) {
			tablero = *ptrTab;
			int contadorJuego = 0;
			salir = false;
			// Ciclo de vida del juego
			cout << "\n" << "NIVEL " << tablero::getNivel(tablero) << "\n";
			cout << tablero;

			while (!reglasJuego::estaTerminado(tablero) && !salir) {
				cout << "\n";
				int x;
				int y;
				cout << WHITE << "INTODUCE DONDE QUIERES COLOCAR/QUITAR UNA BOMBILLA" << "\n";
				cout << WHITE << "Posicion x: ";
				cin >> x;
				cout << WHITE << "Posicion y: ";
				cin >> y;
				if (reglasJuego::esPosQuit(x, y)) {
					salir = true;
					cout << WHITE << "El juego ha acabado, has decidido abandonar." << "\n";

				}
				else {
					jugar(tablero, x, y, contadorJuego);
				}
				cout << "\n";
			}
			if (reglasJuego::estaTerminado(tablero)) {
				cout << WHITE << "Has terminado el nivel " << tablero::getNivel(tablero) << " en " << contadorJuego << " movimientos." << "\n";
				ptrTab = listaTableros::dameTableroSigNivel(tableros, tablero::getNivel(tablero));
				posNivel++;
			}
		}
		if (!salir) {
			cout << "\nHAS COMPLETADO TODOS LOS NIVELES A PARTIR DEL NIVEL " << niv << "!\n";
		}


	}
	else {
		cout << "Archivo no se pudo abrir. Revise si el nombre del archivo esta escrito correctamente\n";
	}

	return 0;

}

void jugar(tTablero& juego, int x, int y, int& nIt) {

	
	if (reglasJuego::esPosReset(x, y)) {

		reglasJuego::resetTablero(juego);
		cout << juego;
		nIt = 0;
		cout << "Se ha reiniciado el tablero.\t Contador: " << nIt << "\n";
	}
	else {
		// El jugador quiere continuar el juego
		reglasJuego::ejecutarPos(juego, x, y);
		cout << juego;
		nIt++;
		cout << "Contador: " << nIt << "\n";
	}

}
