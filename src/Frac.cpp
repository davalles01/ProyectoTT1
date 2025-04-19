// $Source$
// --------------------------------------------------------------------------------------------------------
// Frac.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Frac.cpp
 *  @brief Implementation of the Frac function.
 *
 *  Returns the fractional part of a number (i.e., Frac(x) = x - floor(x)).
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Frac.hpp"

double Frac(double x) {
    return x - std::floor(x);
}
