// $Source$
// --------------------------------------------------------------------------------------------------------
// Frac_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Frac_test.cpp
 *  @brief Test for the Frac function.
 *
 *  Verifies the correctness of the Frac function for several edge cases.
 *  Includes both positive and negative values to test behavior of floor().
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Frac.hpp"
#include <iostream>
#include <assert.h>

/** @brief Simple equality comparison with tolerance */
bool approx_equal(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

/** @brief Frac function test */
void Frac_test() {
    // Test cases
    assert(approx_equal(Frac(3.14), 0.14));
    assert(approx_equal(Frac(-2.75), 0.25));
    assert(approx_equal(Frac(0.0), 0.0));
    assert(approx_equal(Frac(5.0), 0.0));
    assert(approx_equal(Frac(-0.1), 0.9));
}
