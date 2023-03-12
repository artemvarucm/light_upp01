
#include "tablero.h"
using namespace std;




int main() {

	tTablero tablero;

	ifstream archivo;
	tablero::operator>>(archivo, tablero);	
	tablero::operator<<(cout,tablero);
	
	
	
	return 0;
}
