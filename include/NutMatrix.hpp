// $Header$
// --------------------------------------------------------------------------------------------------------
// NutMatrix.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file NutMatrix.hpp
 *  @brief NutMatrix function declaration. Transformation from mean to true equator and equinox
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _NUTMATRIX_
#define _NUTMATRIX_

#include "MeanObliquity.hpp"
#include "NutAngles.hpp"
#include "R_x.hpp"
#include "R_z.hpp"

/** @brief Transformation from mean to true equator and equinox
 *  @param Mjd_TT Modified Julian Date (Terrestrial Time)
 *  @return Nutation matrix
 */
Matrix NutMatrix(double Mjd_TT);

#endif