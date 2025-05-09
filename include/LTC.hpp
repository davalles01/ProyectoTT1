// $Header$
// --------------------------------------------------------------------------------------------------------
// LTC.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file LTC.hpp
 *  @brief LTC function declaration. Transformation from Greenwich meridian system to local tangent coordinates
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _LTC_
#define _LTC_

#include "R_y.hpp"
#include "R_z.hpp"

/** @brief Transformation from Greenwich meridian system to local tangent coordinates
 *  @param lon  Geodetic East longitude [rad]
 *  @param lat  Geodetic latitude [rad]
 *  @return Rotation matrix from the Earth equator and Greenwich meridian to the local tangent (East-North-Zenith) coordinate system
 */
Matrix LTC(double lon, double lat);

#endif