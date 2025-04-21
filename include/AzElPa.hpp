// $Header$
// --------------------------------------------------------------------------------------------------------
// AzElPa.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/21
//
/** @file AzElPa.hpp
 *  @brief AzElPa function header.
 *
 *  Computes azimuth, elevation, and partial derivatives from topocentric coordinates.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _AZELPA_
#define _AZELPA_

#include "matrix.hpp"

/**
 * @brief Computes azimuth, elevation and partial derivatives from local tangent coordinates.
 *
 * @param s     Topocentric local tangent coordinates (East-North-Zenith)
 * @param Az    Azimuth [rad]
 * @param El    Elevation [rad]
 * @param dAds  Partials of azimuth w.r.t. s
 * @param dEds  Partials of elevation w.r.t. s
 */
void AzElPa(Matrix& s, double& Az, double& El, Matrix& dAds, Matrix& dEds);

#endif // _AZELPA_