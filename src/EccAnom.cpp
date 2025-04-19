// $Source$
// --------------------------------------------------------------------------------------------------------
// EccAnom.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file EccAnom.cpp
 *  @brief Implementation of EccAnom function to compute the eccentric anomaly.
 *
 *  Uses the Newton-Raphson method for iterative solving of Kepler's equation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/EccAnom.hpp"
#include "../include/constants.hpp"

using namespace constants;

double EccAnom(double M, double e) {
    const int maxit = 15;
    int i = 1;

    // Normalize M to [0, 2π)
    M = fmod(M, 2.0 * pi);
    if (M < 0) M += 2.0 * pi;

    double E;
    if (e < 0.8) {
        E = M;
    } else {
        E = pi;
    }

    // First iteration
    double f = E - e * sin(E) - M;
    E = E - f / (1.0 - e * cos(E));

    // Newton-Raphson iterations
    while (std::abs(f) > 1e2 * eps) {
        f = E - e * sin(E) - M;
        E = E - f / (1.0 - e * cos(E));
        i++;
        if (i == maxit) {
            cout << "Convergence problems in EccAnom\n";
		    exit(EXIT_FAILURE);
        }
    }

    return E;
}
