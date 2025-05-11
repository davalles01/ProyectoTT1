// $Header$
// --------------------------------------------------------------------------------------------------------
// gast.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file gast.hpp
 *  @brief Header file for the gast function.
 *
 *  Computes Greenwich Apparent Sidereal Time
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _GAST_
#define _GAST_

#include "gmst.hpp"
#include "EqnEquinox.hpp"
#include "constants.hpp"

using namespace constants;

/** 
 * @brief Computes Greenwich Apparent Sidereal Time
 * 
 * @param Mjd_UT1   Modified Julian Date UT1
 * @return GAST in [rad]
 */
double gast(double Mjd_UT1);

#endif