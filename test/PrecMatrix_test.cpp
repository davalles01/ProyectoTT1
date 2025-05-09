// $Source$
// --------------------------------------------------------------------------------------------------------
// PrecMatrix_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file PrecMatrix_test.cpp
 *  @brief Test for the PrecMatrix function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/PrecMatrix.hpp"
#include <assert.h>

/** @brief PrecMatrix test */
void PrecMatrix_test(){

    double Mjd_1 = 51544.5;
    double Mjd_2 = 58000.0;

    Matrix expected_PrecMat(3,3);
    expected_PrecMat(1,1) =  0.999990714344930;  expected_PrecMat(1,2) = -0.003952453738599;  expected_PrecMat(1,3) = -0.001717362326850;
    expected_PrecMat(2,1) =  0.003952453738422;  expected_PrecMat(2,2) =  0.999992189018458;  expected_PrecMat(2,3) = -0.000003394016435;
    expected_PrecMat(3,1) =  0.001717362327258;  expected_PrecMat(3,2) = -0.000003393810230;  expected_PrecMat(3,3) =  0.999998525326472;


    Matrix PrecMat = PrecMatrix(Mjd_1,Mjd_2);

    assert(equals(PrecMat, expected_PrecMat));

}