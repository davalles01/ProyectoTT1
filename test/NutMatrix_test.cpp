// $Source$
// --------------------------------------------------------------------------------------------------------
// NutMatrix_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file NutMatrix_test.cpp
 *  @brief Test for the NutMatrix function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/NutMatrix.hpp"
#include <assert.h>

/** @brief NutMatrix test */
void NutMatrix_test(){

    double Mjd_TT = 58000.0; // Corresponde al 14 de Mayo de 2017

    Matrix expected_NutMat(3,3);
    expected_NutMat(1,1) =  0.999999998893660;  expected_NutMat(1,2) =  0.000043158315066;  expected_NutMat(1,3) =  0.000018709362925;
    expected_NutMat(2,1) = -0.000043158945113;  expected_NutMat(2,2) =  0.999999998501602;  expected_NutMat(2,3) =  0.000033676422804;
    expected_NutMat(3,1) = -0.000018707909479;  expected_NutMat(3,2) = -0.000033677230243;  expected_NutMat(3,3) =  0.999999999257929;

    Matrix NutMat = NutMatrix(Mjd_TT);

    assert(equals(NutMat, expected_NutMat));

}