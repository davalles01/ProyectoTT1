#include "../include/matrix.hpp"
#include <iostream>

int main(){
	
	Matrix M1(3,2);
	M1(1,1) = 5.0;
	
	Matrix M2(3,2);
	M2(1,1) = 3.0;
	
	Matrix M3 = M1 + M2;
	Matrix M4 = M1 - M2;
	Matrix M5 = M2 - M1;
	
	cout << M1 << endl;
	cout << M2 << endl;
	cout << M3 << endl;
	cout << M4 << endl;
	cout << M5 << endl;
	
	Matrix M6(2, 3);
        M6(1,1) = 1.0; M6(1,2) = 2.0; M6(1,3) = 3.0;
        M6(2,1) = 4.0; M6(2,2) = 5.0; M6(2,3) = 6.0;

        Matrix M7(3, 2);
        M7(1,1) = 7.0; M7(1,2) = 8.0;
        M7(2,1) = 9.0; M7(2,2) = 10.0;
        M7(3,1) = 11.0; M7(3,2) = 12.0;

        Matrix M8 = M6 * M7;  // Multiplicamos M1 (2x3) por M2 (3x2)

        cout << "M6:\n" << M6 << endl;
        cout << "M7:\n" << M7 << endl;
        cout << "M8 (M6 * M7):\n" << M8 << endl;
	
	return 0;
}
