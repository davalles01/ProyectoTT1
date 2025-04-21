// $Source$
// --------------------------------------------------------------------------------------------------------
// sign__test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file sign__test.cpp
 *  @brief Test for the sign_ function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/sign_.hpp"
#include <assert.h>

/**
 * @brief Unit test for the sign_ function.
 *
 * Asserts that the function returns the correct value according to the sign of the second argument.
 */
void sign__test() {
    assert(sign_(5.0, 3.0) == 5.0);     // both positive
    assert(sign_(-5.0, 3.0) == 5.0);    // a negative, b positive
    assert(sign_(5.0, -3.0) == -5.0);   // a positive, b negative
    assert(sign_(-5.0, -3.0) == -5.0);  // both negative
    assert(sign_(0.0, -1.0) == -0.0);   // zero with negative sign
    assert(sign_(0.0, 1.0) == 0.0);     // zero with positive sign
}
