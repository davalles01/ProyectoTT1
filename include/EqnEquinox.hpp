// $Header$
// --------------------------------------------------------------------------------------------------------
// EqnEquinox.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file EqnEquinox.hpp
 *  @brief EqnEquinox function declaration, which computes the equation of the equinoxe
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _EQNEQUINOX_
#define _EQNEQUINOX_

#include "NutAngles.hpp"
#include "MeanObliquity.hpp"
#include <cmath>

/** @brief Computes the equation of the equinoxe
 *  @param Mjd_TT Modified Julian Date (Terrestial Time)
 *  @return Equation of the equinoxes
 */
double EqnEquinox(double Mjd_TT);

#endif