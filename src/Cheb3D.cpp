// $Source$
// --------------------------------------------------------------------------------------------------------
// Cheb3D.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file Cheb3D.cpp
 *  @brief Cheb3D function implementation, to evaluate 3D Chebyshev polynomial approximation.
 *  
 *  Uses Clenshaw's algorithm for numerical stability.
 *  
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Cheb3D.hpp"
#include <stdexcept>

Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix Cx, Matrix Cy, Matrix Cz){

    // Check validity
    if ((t < Ta) || (t > Tb)) {
        throw std::runtime_error("ERROR: Time out of range in Cheb3D::Value");
    }

    // Normalized time in [-1, 1]
    double tau = (2 * t - Ta - Tb) / (Tb - Ta);

    Matrix f1 = zeros(3);
    Matrix f2 = zeros(3);
    Matrix f(3);

    for (int i = N; i >= 2; i--) {
        f(1) = Cx(i);
        f(2) = Cy(i);
        f(3) = Cz(i);

        Matrix new_f1 = f1 * (2 * tau) - f2 + f;
        f2 = f1;
        f1 = new_f1;
    }

    Matrix aux2(3);
    aux2(1) = Cx(1);
    aux2(2) = Cy(1);
    aux2(3) = Cz(1);

    return f1 * tau - f2 + aux2; // ChebApp
}