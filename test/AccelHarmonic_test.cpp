// $Source$
// --------------------------------------------------------------------------------------------------------
// AccelHarmonic_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file AccelHarmonic_test.cpp
 *  @brief Test for the AccelHarmonic function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AccelHarmonic.hpp"
#include <assert.h>

/** @brief AccelHarmonic test */
void AccelHarmonic_test(){

    Matrix r = zeros(3);
    r(1) = 7000e3;

    Matrix E = eye(3);

    int n_max = 4;
    int m_max = 4;

    Matrix a = AccelHarmonic(r, E, n_max, m_max);

    Matrix expected_a(3,1);
    expected_a(1,1) = -8.14571105963231; expected_a(2,1) = 1.8418953912846e-05; expected_a(3,1) = 6.13947378070986e-05;

    assert(equals(a,expected_a));
}