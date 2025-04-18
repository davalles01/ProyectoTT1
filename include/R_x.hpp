// $Header$
// --------------------------------------------------------------------------------------------------------
// R_x.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/09
//
/** @file R_x.hpp
 *  @brief R_x function declaration.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------
#ifndef _R_X_
#define _R_X_

#include "./matrix.hpp"
#include <cmath>

/**
 * @brief Computes the vector from a given angle of rotation.
 * @param a Angle of rotation 
 * @return Vector result
 */
Matrix R_x(double angle);

#endif
