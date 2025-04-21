// $Source$
// --------------------------------------------------------------------------------------------------------
// timediff_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file timediff_test.cpp
 *  @brief Test for the timediff function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/timediff.hpp"
#include <cassert>
#include <cmath>

/**
 * @brief Unit test for the timediff function.
 *
 * Verifies the correctness of time differences computed for known UT1_UTC and TAI_UTC values.
 */
void timediff_test() {
    double UT1_UTC = 0.3341;
    double TAI_UTC = 37.0;

    double UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC;
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);

    assert(std::abs(UT1_TAI - (-36.6659)) < 1e-10);
    assert(std::abs(UTC_GPS - (-18.0)) < 1e-10);
    assert(std::abs(UT1_GPS - (-17.6659)) < 1e-10);
    assert(std::abs(TT_UTC - 69.184) < 1e-10);
    assert(std::abs(GPS_UTC - 18.0) < 1e-10);
}
