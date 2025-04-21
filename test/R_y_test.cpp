// $Source$
// --------------------------------------------------------------------------------------------------------
// R_y_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file R_y_test.cpp
 *  @brief Test for the R_y function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/R_y.hpp"
#include "../include/constants.hpp"
#include <assert.h>
#include <cmath>

using namespace constants;

/**
 * @brief Unit test for the R_y function.
 *
 * Asserts that the generated rotation matrix matches expected values for a known input angle.
 */
void R_y_test() {
    double angle = pi / 4;  // 45 degrees
    Matrix R = R_y(angle);

    Matrix expected(3,3);
    expected(1,1) =   0.707106781186548;  expected(1,2) = 0.0;  expected(1,3) = -0.707106781186547;
    expected(2,1) = 0.0;  expected(2,2) = 1.0;  expected(2,3) = 0.0;
    expected(3,1) = 0.707106781186547;  expected(3,2) = 0.0;  expected(3,3) = 0.707106781186548;

    assert(equals(R,expected));
}