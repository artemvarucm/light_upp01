#include<iostream>
using namespace std;

#include "celda.h"

using namespace celda;
int main(){
	tCelda celda;
	
	celda.tipo = PARED;
	
	celda.numBombillas = 1;
	char res;
	
	
	res = celdaToChar(celda);
	
	cout << res << endl;

}