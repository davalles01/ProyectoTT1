// $Source$
// --------------------------------------------------------------------------------------------------------
// gmst_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file gmst_test.cpp
 *  @brief Test for the gmst function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/gmst.hpp"
#include <assert.h>
#include <cmath>

/** @brief gmst test */
void gmst_test(){

    double Mjd_UT1 = 51544.5;

    double gmstime = gmst(Mjd_UT1);
    double expected_gmstime = 4.894961212823057;
    
    assert(std::abs(gmstime - expected_gmstime) < 1e-12);
}