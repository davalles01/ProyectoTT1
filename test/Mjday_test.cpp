// $Source$
// --------------------------------------------------------------------------------------------------------
// Mjday_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Mjday_test.cpp
 *  @brief Test for the Mjday function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Mjday.hpp"
#include <iostream>
#include <assert.h>

/** @brief Mjday test */
void Mjday_test() {
    // Test input: 2024, 3, 15, 12, 0, 0 (March 15, 2024, at 12:00:00)
    int year = 2024;
    int month = 3;
    int day = 15;
    int hour = 12;
    int minute = 0;
    double second = 0.0;
    
    double expected_MJD = 6.038450000000000e+04;  // Expected MJD for this date

    double result = Mjday(year, month, day, hour, minute, second);

    // Comprobar que el resultado está dentro de un margen de error
    assert(std::abs(result - expected_MJD) < 1e-10);
}
