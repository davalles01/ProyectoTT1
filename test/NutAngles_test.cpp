// $Source$
// --------------------------------------------------------------------------------------------------------
// NutAngles_test.cpp
// --------------------------------------------------------------------------------------------------------

/** @file NutAngles_test.cpp
 *  @brief Unit test for the NutAngles function.
 *
 *  This test checks the correctness of the NutAngles function implementation by comparing
 *  the output angles with expected values for a specific input.
 *
 *  @author Daniel Vallés Belloso
 *  @date May 5, 2025
 *  @bug No known bugs.
 */

 #include <iostream>
 #include "../include/NutAngles.hpp"
 #include "../include/matrix.hpp"
 #include <assert.h>

void NutAngles_test() {
    // Input
    double Mjd_TT = 51544.5;

    // Call function
    auto [dpsi, deps] = NutAngles(Mjd_TT);

    // Expected values from MATLAB
    double expected_dpsi = -6.750247617532479e-05;
    double expected_deps = -2.799221238377013e-05;

    // Compare with tolerance
    assert(equals(dpsi, expected_dpsi));
    assert(equals(deps, expected_deps));
}
 