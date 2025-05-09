// $Source$
// --------------------------------------------------------------------------------------------------------
// LTC_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file LTC_test.cpp
 *  @brief Test for the LTC function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/LTC.hpp"
#include <assert.h>

/** @brief LTC test */
void LTC_test(){

    double lon = 0;
    double lat = 0.898441393719869;
    
    Matrix expected_M(3,3);
    expected_M(1,1) = 0.0; expected_M(1,2) = 1.0; expected_M(1,3) = 0.0;
    expected_M(2,1) = -0.782357113369766; expected_M(2,2) = 0.0; expected_M(2,3) = 0.622830110993140;
    expected_M(3,1) = 0.622830110993140; expected_M(3,2) = 0.0; expected_M(3,3) = 0.782357113369766;

    Matrix M = LTC(lon,lat);

    assert(equals(M,expected_M));

}