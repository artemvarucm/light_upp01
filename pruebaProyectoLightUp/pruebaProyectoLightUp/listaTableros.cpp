#include "tablero.h"
#include "listaTableros.h"



void listaTableros::inicializaVectorTablero(tListaTableros& losTableros) {
	losTableros.nElem = 0;
}

istream& listaTableros::operator>> (ifstream& in, tListaTableros& losTableros) {
	tTablero tablero;
	int nTableros;
	in >> nTableros;
	for (int i = 0; i < nTableros; i++) {
		int nivel;
		//getline(in, nivel);
		in.ignore(6,' ');
		in >> nivel;
		/*int nivelint;
		nivelint = nivel[6] - '0';*/
		tablero::operator>>(in, tablero);
		tablero.nivel = nivel;
		tPtrTablero ptrTablero = new tTablero(tablero);
		listaTableros::insertarOrdTablero(losTableros, ptrTablero);
	}
	return in;
}

void listaTableros::insertarOrdTablero(tListaTableros& losTableros, tPtrTablero const& elTablero) {
	if (losTableros.nElem < MAX_TABLEROS) {
		int nivTab = tablero::getNivel(*elTablero);
		int i = 0;

		while (i < losTableros.nElem && tablero::getNivel(*losTableros.datos[i]) < nivTab) {
			i++;
		}
		for (int j = losTableros.nElem; j > i; j--) {
			losTableros.datos[j] = losTableros.datos[j - 1];
		}

		losTableros.datos[i] = elTablero;
		losTableros.nElem++;
	}
	else {
		cout << "Lista Llena\n";
	}

}
