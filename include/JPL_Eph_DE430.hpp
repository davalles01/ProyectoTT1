// $Header$
// --------------------------------------------------------------------------------------------------------
// JPL_Eph_DE430.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file JPL_Eph_DE430.hpp
 *  @brief JPL_Eph_DE430 function declaration. Computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _JPL_EPH_DE430_
#define _JPL_EPH_DE430_

#include "matrix.hpp"
#include "Cheb3D.hpp"
#include "SAT_Const.hpp"
#include "global.hpp"

using namespace consts;

/**
 * @brief Computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides
 * 
 * @param Mjd_TDB Modified julian date of TDB  
 * @return r_Earth(solar system barycenter (SSB)),r_Mars,r_Mercury,r_Venus,
 *   r_Jupiter,r_Saturn,r_Uranus,r_Neptune,r_Pluto,r_Moon,
 *   r_Sun(geocentric equatorial position ([m]) referred to the
 *   International Celestial Reference Frame (ICRF))     
 */
tuple<Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix> JPL_Eph_DE430(double Mjd_TDB);

#endif