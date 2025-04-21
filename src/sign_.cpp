// $Source$
// --------------------------------------------------------------------------------------------------------
// sign_.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file sign_.cpp
 *  @brief sign_ function implementation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/sign_.hpp"
#include <cmath>

double sign_(double a, double b) {
    return (b >= 0.0) ? std::abs(a) : -std::abs(a);
}
