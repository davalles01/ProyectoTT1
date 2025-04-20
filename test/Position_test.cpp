// $Source$
// --------------------------------------------------------------------------------------------------------
// Position_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file Position_test.cpp
 *  @brief Test for the Position function using assert.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Position.hpp"
#include <assert.h>
#include <cmath>
#include <iostream>

using namespace std;


void Position_test() {
    // Input values: longitude, latitude in radians, altitude in meters
    double lon = 1.0;           // ≈ 57.3°
    double lat = 0.5;           // ≈ 28.6°
    double h = 1000.0;          // 1 km altitude

    Matrix result = Position(lon, lat, h);
    
    // Obtenidos en MATLAB
    Matrix expected(3);
    expected(1) = 3.027060239398717;
    expected(2) = 4.714366999835280;
    expected(3) = 3.040190332390430;

    expected = expected * 1.0e+6;

    assert(abs(result(1) - expected(1)) < 1e-5);
    assert(abs(result(2) - expected(2)) < 1e-5);
    assert(abs(result(3) - expected(3)) < 1e-5);
}
