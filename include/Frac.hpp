// $Header$
// --------------------------------------------------------------------------------------------------------
// Frac.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Frac.hpp
 *  @brief Header file for the Frac function.
 *
 *  Computes the fractional part of a number (i.e., Frac(x) = x - floor(x)).
 *  Useful for keeping angles or time values within certain bounds.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _FRAC_
#define _FRAC_

#include <cmath>

/** 
 * @brief Computes the fractional part of a number.
 * 
 * @param x Input value (can be positive or negative)
 * @return Fractional part of x (always in the range [0, 1))
 */
double Frac(double x);

#endif // FRAC_