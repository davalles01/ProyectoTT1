// $Source$
// --------------------------------------------------------------------------------------------------------
// JPL_Eph_DE430_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file JPL_Eph_DE430_test.cpp
 *  @brief Test for the JPL_Eph_DE430 function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/JPL_Eph_DE430.hpp"
#include <assert.h>

/** @brief JPL_Eph_DE430 test */
void JPL_Eph_DE430_test(){

    double Mjd_TDB = 60000;

    Matrix r_Earth = JPL_Eph_DE430(Mjd_TDB);

    Matrix expected_r_Earth(3,1);
    expected_r_Earth(1,1) = -1.363821272400698;
    expected_r_Earth(2,1) = 0.556380040694172;
    expected_r_Earth(3,1) = 0.241540011325855;

    expected_r_Earth = expected_r_Earth * 1.0e+11;

    cout << "r_Earth: " << endl << r_Earth(1,1) << endl << r_Earth(2,1) << endl << r_Earth(3,1) << endl;

    assert(equals(r_Earth,expected_r_Earth));
}