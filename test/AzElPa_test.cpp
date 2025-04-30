// $Source$
// --------------------------------------------------------------------------------------------------------
// AzElPa_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/21
//
/** @file AzElPa_test.cpp
 *  @brief Unit test for the AzElPa function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AzElPa.hpp"
#include "../include/constants.hpp"
#include <assert.h>
#include <cmath>

using namespace constants;

/**
 * @brief Unit test for the AzElPa function.
 *
 * Asserts that the generated azimuth, elevation, and partials match expected values for a known input vector.
 */
void AzElPa_test() {
    Matrix s(3);
    s(1) = 1.0;  // East component
    s(2) = 1.0;  // North component
    s(3) = 1.0;  // Zenith component

    double Az, El;
    Matrix dAds(3), dEds(3);

    tie(Az, El, dAds, dEds) = AzElPa(s);

    // Expected values based on the input (1,1,1)
    assert(fabs(Az - 0.785398163397448) < 1e-7);
    assert(fabs(El - 0.615479708670387) < 1e-7);
    assert(fabs(dAds(1) - 0.5) < 1e-7);
    assert(fabs(dAds(2) + 0.5) < 1e-7);
    assert(fabs(dAds(3) - 0.0) < 1e-7);
    assert(fabs(dEds(1) + 0.235702260395516) < 1e-7);
    assert(fabs(dEds(2) + 0.235702260395516) < 1e-7);
    assert(fabs(dEds(3) - 0.471404520791032) < 1e-7);
}
