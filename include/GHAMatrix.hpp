// $Header$
// --------------------------------------------------------------------------------------------------------
// GHAMatrix.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file GHAMatrix.hpp
 *  @brief Header file for the GHAMatrix function.
 *
 *  Computes the transformation matrix from the true equator and equinox system 
 *  to the Earth equator and Greenwich meridian system using the Greenwich Hour Angle.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _GHAMATRIX_
#define _GHAMATRIX_

#include "R_z.hpp"
#include "gast.hpp"

/**
 * @brief Computes the transformation matrix from the true equator and equinox system 
 *  to the Earth equator and Greenwich meridian system
 * 
 *  @param Mjd_UT1 Modified Julian Date in UT1 time scale.
 *  @return GHAmat 3×3 rotation matrix representing the Greenwich Hour Angle transformation.
 * 
 */
Matrix GHAMatrix(double Mjd_UT1);

#endif