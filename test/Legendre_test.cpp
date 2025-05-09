// $Source$
// --------------------------------------------------------------------------------------------------------
// Legendre_test.cpp
// --------------------------------------------------------------------------------------------------------

/** @file Legendre_test.cpp
 *  @brief Unit test for the Legendre function.
 *
 *  This test checks the correctness of the Legendre function implementation by comparing
 *  the output matrices `pnm` and `dpnm` with expected values for a specific input.
 *
 *  @author Daniel Vallés Belloso
 *  @date May 5, 2025
 *  @bug No known bugs.
 */

 #include <iostream>
 #include "../include/Legendre.hpp"
 #include "../include/matrix.hpp"

 void printMatrix(Matrix& mat, const std::string& name) {
    std::cout << name << ":\n";
    for (int i = 1; i <= mat.n_row; ++i) {
        for (int j = 1; j <= mat.n_column; ++j) {
            std::cout << mat(i, j) << "\t";
        }
        std::cout << "\n";
    }
}
 
 void Legendre_test() {
     // Parámetros de entrada
     int n = 5;
     int m = 3;
     double fi = M_PI / 4;

     // Ejecutar la función Legendre
     auto [pnm, dpnm] = Legendre(n, m, fi);
 
    // Matriz esperada pnm (6x6)
    Matrix expected_pnm = zeros(6, 6);
    expected_pnm(1,1) = 1.00000;
    
    expected_pnm(2,1) = 1.22474; expected_pnm(2,2) = 1.22474;
    
    expected_pnm(3,1) = 0.559017; expected_pnm(3,2) = 1.93649; expected_pnm(3,3) = 0.968246;
    
    expected_pnm(4,1) = -0.467707; expected_pnm(4,2) = 1.71847; expected_pnm(4,3) = 1.81142; expected_pnm(4,4) = 0.73951;
    
    expected_pnm(5,1) = -1.21875; expected_pnm(5,2) = 0.592927; expected_pnm(5,3) = 2.09631; expected_pnm(5,4) = 1.56874; expected_pnm(5,5) = 0.554632;
    
    expected_pnm(6,1) = -1.24589; expected_pnm(6,2) = -0.851527; expected_pnm(6,3) = 1.50195; expected_pnm(6,4) = 2.14609; expected_pnm(6,5) = 1.30073; expected_pnm(6,6) = 0.411326;
    
    // Matriz esperada dpnm (6x6)
    Matrix expected_dpnm = zeros(6, 6);
    expected_dpnm(2,1) = 1.22474; expected_dpnm(2,2) = -1.22474;
    
    expected_dpnm(3,1) = 3.3541; expected_dpnm(3,2) = 7.4476e-16; expected_dpnm(3,3) = -1.93649;
    
    expected_dpnm(4,1) = 4.20936; expected_dpnm(4,2) = 4.00975; expected_dpnm(4,3) = -1.81142; expected_dpnm(4,4) = -2.21853;
    
    expected_dpnm(5,1) = 1.875; expected_dpnm(5,2) = 8.30098; expected_dpnm(5,3) = 1.67705; expected_dpnm(5,4) = -3.13748; expected_dpnm(5,5) = -2.21853;
    
    expected_dpnm(6,1) = -3.29795; expected_dpnm(6,2) = 8.79911; expected_dpnm(6,3) = 7.50976; expected_dpnm(6,4) = -0.919754; expected_dpnm(6,5) = -3.90219; expected_dpnm(6,6) = -2.05663;
    
    assert(equals(pnm, expected_pnm));
    assert(equals(dpnm, expected_dpnm));
 }
 