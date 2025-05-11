#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include "It1_tests.cpp"
#include "It2_tests.cpp"
#include "It3_tests.cpp"
#include <iostream>

int main(){

	// Carga de archivos
    eop19620101(21413); // Cargar solo las primeras c líneas del archivo eop19620101.txt
	GGM03S(); // Cargamos las matrices Cnm y Snm
	DE430Coeff(); // Cargamos la matriz PC

	// AuxParam
	AuxParam.Mjd_UTC = 49746.1112847221;
	AuxParam.Mjd_TT = 49746.1108586111;
	AuxParam.n = 20;
	AuxParam.m = 20;
	AuxParam.sun = 1;
	AuxParam.moon = 1;
	AuxParam.planets = 1;

	//It1_tests();
	//It2_tests();
	It3_tests();
	
	return 0;
}
