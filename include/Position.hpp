// $Header$
// --------------------------------------------------------------------------------------------------------
// Position.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file Position.hpp
 *  @brief Computes the position vector from geodetic coordinates.
 *
 *  Converts longitude [rad], latitude [rad], and altitude [m] into a 
 *  position vector in meters.
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _POSITION_HPP
#define _POSITION_HPP

#include "matrix.hpp"

/**
 * @brief Computes position vector from geodetic coordinates.
 *
 * @param lon Longitude in radians
 * @param lat Latitude in radians
 * @param h Altitude above ellipsoid in meters
 * @return Position vector in meters as a row vector (1x3)
 */
Matrix Position(double lon, double lat, double h);

#endif // _POSITION_HPP
