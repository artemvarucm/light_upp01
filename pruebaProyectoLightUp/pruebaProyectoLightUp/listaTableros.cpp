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

ostream& listaTableros::operator<< (ostream& out, tListaTableros const& losTableros) {
	for (int i = 0; i < losTableros.nElem; i++) {
		cout << "\n\n";
		cout << "NIVEL: " << tablero::getNivel(*(losTableros.datos[i])) << "\n\n";
		tablero::operator<<(out, *losTableros.datos[i]);
	}
	return out;
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


tPtrTablero listaTableros::dameTableroNivel(tListaTableros const& losTableros, int nivel, int &posNivel) {
	
	tPtrTablero tabNiv = NULL;
	if (listaTableros::hayTableroNivel(losTableros, nivel, posNivel)) {
		tabNiv = losTableros.datos[posNivel];
	}
	return tabNiv;
}


tPtrTablero listaTableros::dameTableroSigNivel(tListaTableros const& losTableros, int nivel) {
	int posNivel;
	tPtrTablero tabNiv = NULL;
	if (listaTableros::hayTableroNivel(losTableros, nivel, posNivel) && ((posNivel + 1) < losTableros.nElem)) {
		tabNiv = losTableros.datos[posNivel + 1];
	}
	return tabNiv;
}



bool listaTableros::hayTableroNivel(tListaTableros const& losTableros, int nivel, int& posNivel) {
	int ini = 0, fin = losTableros.nElem - 1, mitad;
	bool encontrado = false;
	while (!encontrado && ini <= fin) {
		mitad = (ini + fin) / 2;
		if (tablero::getNivel(*losTableros.datos[mitad]) == nivel) {
			encontrado = true;
		} else if (tablero::getNivel(*losTableros.datos[mitad]) < nivel) {
			ini = mitad + 1;
		} else {
			fin = mitad - 1;
		}
		
	}
	posNivel = mitad;
	return encontrado;
}

void listaTableros::deleteListaTablero(tListaTableros& losTableros) {
	for (int i = 0; i < losTableros.nElem; i++) {
		delete losTableros.datos[i];
	}
	losTableros.nElem = 0;
}
