// $Source$
// --------------------------------------------------------------------------------------------------------
// PoleMatrix_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file PoleMatrix_test.cpp
 *  @brief Test for the PoleMatrix function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/PoleMatrix.hpp"
#include <assert.h>

/** @brief PoleMatrix test */
void PoleMatrix_test(){

    double xp = 0.1 * M_PI / 180 / 3600;
    double yp = -0.2 * M_PI / 180 / 3600;

    Matrix expected_PoleMat(3,3);
    expected_PoleMat(1,1) =  0.999999999999882;  expected_PoleMat(1,2) = -0.000000000000470;  expected_PoleMat(1,3) =  0.000000484813681;
    expected_PoleMat(2,1) =  0.000000000000000;  expected_PoleMat(2,2) =  0.999999999999530;  expected_PoleMat(2,3) =  0.000000969627362;
    expected_PoleMat(3,1) = -0.000000484813681;  expected_PoleMat(3,2) = -0.000000969627362;  expected_PoleMat(3,3) =  0.999999999999410;

    Matrix PoleMat = PoleMatrix(xp,yp);

    assert(equals(PoleMat, expected_PoleMat));

}