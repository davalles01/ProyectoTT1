// $Header$
// --------------------------------------------------------------------------------------------------------
// Gmst.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file Gmst.hpp
 *  @brief Gmst function declaration. Greenwich Mean Sidereal Time
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _GMST_
#define _GMST_

#include "SAT_Const.hpp"
#include "Frac.hpp"

using namespace consts;

/** @brief Greenwich Mean Sidereal Time
 *  @param Mjd_UT1  Modified Julian Date UT1
 *  @return GMST in [rad]
 */
double gmst(double Mjd_UT1);

#endif