// $Source$
// --------------------------------------------------------------------------------------------------------
// EqnEquinox_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/21
//
/** @file EqnEquinox_test.cpp
 *  @brief Unit test for the EqnEquinox function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/EqnEquinox.hpp"
#include <assert.h>
#include <cmath>

bool equals(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

/**
 * @brief Unit test for the EqnEquinox function.
 *
 * Computes the equation of the equinox
 */
void EqnEquinox_test() {
    
    double Mjd_TT = 58000.0; // Corresponde al 14 de Mayo de 2017

    double expected_EqE = -4.315831508180012e-05;

    double EqE = EqnEquinox(Mjd_TT);

    assert(equals(EqE,expected_EqE));
}
