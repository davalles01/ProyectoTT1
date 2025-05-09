// $Header$
// --------------------------------------------------------------------------------------------------------
// PrecMatrix.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file PrecMatrix.hpp
 *  @brief PrecMatrix function declaration. Precession transformation of equatorial coordinates
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _PRECMATRIX_
#define _PRECMATRIX_

#include "R_z.hpp"
#include "R_y.hpp"
#include "SAT_Const.hpp"

using namespace consts;

/** @brief Transformation from pseudo Earth-fixed to Earth-fixed coordinates for a given date
 *  @param Mjd_1 Epoch given (Modified Julian Date TT)
 *  @param Mjd_2 Epoch to precess to (Modified Julian Date TT)
 *  @return Precession transformation matrix
 */
Matrix PrecMatrix(double Mjd_1, double Mjd_2);

#endif