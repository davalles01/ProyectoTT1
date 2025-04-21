// $Header$
// --------------------------------------------------------------------------------------------------------
// R_y.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file R_y.hpp
 *  @brief Generates a rotation matrix around the Y axis.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _R_Y_
#define _R_Y_

#include "matrix.hpp"

/**
 * @brief Returns the rotation matrix around the Y axis.
 *
 * @param angle Angle of rotation in radians.
 * @return 3x3 rotation matrix.
 */
Matrix R_y(double angle);

#endif // _R_Y_
