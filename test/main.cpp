#include "../include/matrix.hpp"
#include "../include/global.hpp"
#include "It1_tests.cpp"
#include "It2_tests.cpp"
#include <iostream>

int main(){

	// Carga de matrices
	DE430Coeff(); // Cargamos la matriz PC

	//It1_tests();
	It2_tests();
	
	return 0;
}
