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

    Matrix r = zeros(3,1);
    r(1,1) = 7000e3;

    Matrix E = eye(3);

    int n_max = 4;
    int m_max = 4;

    Matrix a = AccelHarmonic(r, E, n_max, m_max);

    cout << "a: \n" << a(1,1) << endl << a(2,1) << endl << a(3,1) << endl;
}