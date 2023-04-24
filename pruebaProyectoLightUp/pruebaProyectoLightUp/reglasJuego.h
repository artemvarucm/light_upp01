#ifndef REGH
#define REGH
#include "tablero.h"

namespace reglasJuego {
	bool estaTerminado(const tTablero& juego);
	bool esPosQuit(int x, int y);
	bool esPosReset(int x, int y);
	void ejecutarPos(tTablero& tab, int x, int y);
	void resetTablero(tTablero& tab);

}

#endif
