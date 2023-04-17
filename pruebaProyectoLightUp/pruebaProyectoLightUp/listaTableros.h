#ifndef LISTATABH
#define LISTATABH
#include "tablero.h"
#include <string>

const int MAX_TABLEROS = 20;

typedef tTablero* tPtrTablero;

struct tListaTableros {
	int nElem;
	tPtrTablero datos[MAX_TABLEROS];
};
namespace listaTableros {
	istream& operator>> (ifstream& in, tListaTableros& losTableros);

	ostream& operator<< (ostream& out, tListaTableros const& losTableros);

	void inicializaVectorTablero(tListaTableros& losTableros);

	bool hayTableroNivel(tListaTableros const& losTableros, int nivel);

	tPtrTablero dameTableroNivel(tListaTableros const& losTableros, int nivel);

	tPtrTablero dameTableroSigNivel(tListaTableros const& losTableros, int nivel);

	void insertarOrdTablero(tListaTableros& losTableros, tPtrTablero const& elTablero);

	void deleteListaTablero(tListaTableros& losTableros);

	void inicializaVectorTablero(tListaTableros& losTableros);
}

#endif