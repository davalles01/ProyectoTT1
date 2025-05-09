// $Header$
// --------------------------------------------------------------------------------------------------------
// PoleMatrix.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file PoleMatrix.hpp
 *  @brief PoleMatrix function declaration. Transformation from pseudo Earth-fixed to Earth-fixed coordinates for a given date
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _POLEMATRIX_
#define _POLEMATRIX_

#include "R_x.hpp"
#include "R_y.hpp"

/** @brief Transformation from pseudo Earth-fixed to Earth-fixed coordinates for a given date
 *  @param xp Pole coordinate x
 *  @param yp Pole coordinate y
 *  @return Pole matrix
 */
Matrix PoleMatrix(double xp, double yp);

#endif