// $Source$
// --------------------------------------------------------------------------------------------------------
// Cheb3D.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file Cheb3D.cpp
 *  @brief Test for the Cheb3D function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Cheb3D.hpp"
#include <assert.h>

/** @brief Cheb3D test */
void Cheb3D_test(){
    
    int N = 3;
    double Ta = 0.0;
    double Tb = 10.0;
    double t = 3.0;
    
    Matrix Cx(3);
    Cx(1) = 1.0;  Cx(2) = 0.5;   Cx(3) = -0.2;
    
    Matrix Cy(3);
    Cy(1) = 0.0;  Cy(2) = 1.0;   Cy(3) = 0.3;
    
    Matrix Cz(3);
    Cz(1) = 2.0;  Cz(2) = -0.5;  Cz(3) = 0.1;
    
    Matrix expected(3);
    expected(1) = 0.936; expected(2) = -0.604; expected(3) = 2.132;

    Matrix result = Cheb3D(t, N, Ta, Tb, Cx, Cy, Cz);
    
    std::cout << "Resultado:\n";
    for (int i = 1; i <= 3; ++i) {
        std::cout << result(i) << " ";
    }
    std::cout << "\nEsperado:\n";
    for (int i = 1; i <= 3; ++i) {
        std::cout << expected(i) << " ";
    }
    std::cout << std::endl;
    

    assert(equals(expected, result));

}