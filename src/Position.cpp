// $Source$
// --------------------------------------------------------------------------------------------------------
// Position.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file Position.cpp
 *  @brief Position function implementation, computing position from geodetic coordinates.
 * 
 *  Uses WGS84 ellipsoid constants from constants.hpp.
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Position.hpp"
#include "../include/constants.hpp"
#include <cmath>

using namespace constants;

Matrix Position(double lon, double lat, double h) {
    const double R_equ = R_Earth;
    const double f = f_Earth;

    const double e2 = f * (2.0 - f); // Square of eccentricity
    const double CosLat = std::cos(lat);
    const double SinLat = std::sin(lat);

    const double N = R_equ / std::sqrt(1.0 - e2 * SinLat * SinLat);

    Matrix r(3);
    r(1) = (N + h) * CosLat * std::cos(lon);
    r(2) = (N + h) * CosLat * std::sin(lon);
    r(3) = ((1.0 - e2) * N + h) * SinLat;

    return r;
}
