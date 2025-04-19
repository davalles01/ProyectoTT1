// $Source$
// --------------------------------------------------------------------------------------------------------
// MeanObliquity_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file MeanObliquity_test.cpp
 *  @brief Test for the MeanObliquity function.
 *
 *  Uses a known value near J2000 to verify correctness.
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/MeanObliquity.hpp"
#include "../include/constants.hpp"
#include <cmath>
#include <assert.h>

using namespace constants;

/** @brief Test the MeanObliquity function with a known value */
void MeanObliquity_test() {
    double Mjd_TT = MJD_J2000;  // Epoch J2000.0

    double result = MeanObliquity(Mjd_TT);

    // Valor esperado en radianes: 84381.448 arcsec = 0.409092804 rad
    double expected = 0.409092804;

    assert(std::abs(result - expected) < 1e-4);
}
