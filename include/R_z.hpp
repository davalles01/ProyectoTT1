// $Header$
// --------------------------------------------------------------------------------------------------------
// R_z.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file R_z.hpp
 *  @brief R_z function declaration.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _R_Z_
#define _R_Z_

#include "matrix.hpp"

/**
 * @brief Computes the rotation matrix around the Z-axis.
 * 
 * @param angle Rotation angle in radians.
 * @return A 3x3 rotation matrix.
 */
Matrix R_z(double angle);

#endif // _R_Z_
