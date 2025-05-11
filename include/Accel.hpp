// $Header$
// --------------------------------------------------------------------------------------------------------
// Accel.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file Accel.hpp
 *  @brief Header file for the Accel function.
 *
 *  Computes the acceleration of an Earth-orbiting satellite due to:
 *  - the Earth's harmonic gravity field,
 *  - the gravitational perturbations of the Sun and Moon,
 *  - the solar radiation pressure,
 *  - the atmospheric drag.
 *
 *
 *  @author Daniel Vallés Belloso
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _ACCEL_
#define _ACCEL_

#include "matrix.hpp"
#include "IERS.hpp"
#include "AccelPointMass.hpp"
#include "AccelHarmonic.hpp"
#include "global.hpp"
#include "Mjday_TDB.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "PrecMatrix.hpp"
#include "GHAMatrix.hpp"
#include "timediff.hpp"
#include "JPL_Eph_DE430.hpp"
#include "SAT_Const.hpp"

using namespace consts;

/**
 * @brief Computes the acceleration of an Earth-orbiting satellite
 * 
 *  @param x Terrestrial Time (Modified Julian Date)
 *  @param Y      Satellite state vector in the ICRF/EME2000 system
 *  @return       Acceleration vector (a = d²r/dt²) in the ICRF/EME2000 system
 */

 Matrix Accel(double x, Matrix Y);

#endif
