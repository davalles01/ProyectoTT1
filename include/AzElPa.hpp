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
 * @return tuple<> A tuple with the values of azimuth, elevation and partial derivatives coordinates
 */
 
tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s);

#endif // _AZELPA_