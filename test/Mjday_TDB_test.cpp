// $Source$
// --------------------------------------------------------------------------------------------------------
// Mjday_TDB_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file Mjday_TDB_test.cpp
 *  @brief Unit test for the Mjday_TDB function.
 *
 *  Verifies that the function computes a correct TDB value for a known TT input.
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include "../include/Mjday_TDB.hpp"

/**
 * @brief Unit test for Mjday_TDB function.
 */
void Mjday_TDB_test() {
    double Mjd_TT = 60384.0;       // 2024-03-15 12:00:00 TT
    double Mjd_TDB = Mjday_TDB(Mjd_TT);

    // Expected value computed from MATLAB
    double expected = 6.038400000001785e+04;
    double tolerance = 1e-10;

    assert(std::abs(Mjd_TDB - expected) < tolerance);
}
