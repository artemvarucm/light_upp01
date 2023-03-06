#include <iostream>

#include "colors.h"
#include <iomanip>
#include "celda.h"
using namespace std;




const int HUECOS = 2;
const int N = 5;

void mostrarCoutSeparadorMat() {
	cout << "\t -+";
	for (int col = 0; col < N; ++col) {
		cout << setw(HUECOS + 2) << setfill('-') << '+' << setfill(' ');
	}
	cout << endl;
}


int main() {
	tCelda c;
	cout << celda::celdaToChar(c);

	return 0;
}