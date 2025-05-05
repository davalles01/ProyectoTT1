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
     printMatrix(pnm, "pnm");
 
    // Matriz esperada pnm (6x6)
     Matrix expected_pnm = zeros(6, 6);
     expected_pnm(1,1) = 1.0000;

     expected_pnm(2,1) = 1.2247; expected_pnm(2,2) = 1.2247;
 
     expected_pnm(3,1) = 0.5590; expected_pnm(3,2) = 1.9365; expected_pnm(3,3) = 0.9682;

     expected_pnm(4,1) = -0.4677; expected_pnm(4,2) = 1.7185; expected_pnm(4,3) = 1.8114; expected_pnm(4,4) = 0.7395;

     expected_pnm(5,1) = -1.2188; expected_pnm(5,2) = 0.5929; expected_pnm(5,3) = 2.0963; expected_pnm(5,4) = 1.5687; expected_pnm(5,5) = 0.5546;

     expected_pnm(6,1) = -1.2459; expected_pnm(6,2) = -0.8515; expected_pnm(6,3) = 1.5020; expected_pnm(6,4) = 2.1461; expected_pnm(6,5) = 1.3007; expected_pnm(6,6) = 0.4113;

     printMatrix(expected_pnm, "expected_pnm");
     printMatrix(dpnm, "dpnm");
     // Matriz esperada dpnm (6x6)
     Matrix expected_dpnm = zeros(6, 6);
     expected_dpnm(2,1) = 1.2247; expected_dpnm(2,2) = -1.2247;

     expected_dpnm(3,1) = 3.3541; expected_dpnm(3,2) = 0.0000; expected_dpnm(3,3) = -1.9365;
 
     expected_dpnm(4,1) = 4.2094; expected_dpnm(4,2) = 4.0098; expected_dpnm(4,3) = -1.8114; expected_dpnm(4,4) = -2.2185;

     expected_dpnm(5,1) = 1.8750; expected_dpnm(5,2) = 8.3010; expected_dpnm(5,3) = 1.6771; expected_dpnm(5,4) = -3.1375; expected_dpnm(5,5) = -2.2185;

     expected_dpnm(6,1) = -3.2979; expected_dpnm(6,2) = 8.7991; expected_dpnm(6,3) = 7.5098; expected_dpnm(6,4) = -0.9198; expected_dpnm(6,5) = -3.9022; expected_dpnm(6,6) = -2.0566;

     printMatrix(expected_dpnm, "expected_dpnm");

     // Validación
     if (equals(pnm, expected_pnm) && equals(dpnm, expected_dpnm)) {
         std::cout << "Legendre_test passed successfully." << std::endl;
     } else {
         std::cout << "Legendre_test failed." << std::endl;
     }
 }
 