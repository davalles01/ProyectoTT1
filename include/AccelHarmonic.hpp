// $Header$
// --------------------------------------------------------------------------------------------------------
// AccelHarmonic.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file AccelHarmonic.hpp
 *  @brief AccelHarmonic function declaration. Computes the acceleration due to the harmonic gravity field of the central body
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _ACCELHARMONIC_
#define _ACCELHARMONIC_

#include "matrix.hpp"
#include "Legendre.hpp"
#include "SAT_Const.hpp"
#include "global.hpp"

using namespace consts;

/**
 * @brief Computes the gravitational acceleration on a satellite due to the Earth's 
 *        harmonic gravity field.
 *
 * This function calculates the acceleration vector acting on a satellite using the
 * spherical harmonic model of the Earth's gravity field, based on its inertial position
 * and a transformation to the body-fixed frame.
 *
 * @param r      Satellite position vector in the inertial system (3x1)
 * @param E      Transformation matrix to the body-fixed system (3x1)
 * @param n_max  Maximum degree of spherical harmonics.
 * @param m_max  Maximum order of spherical harmonics (m_max ≤ n_max; m_max = 0 for zonal terms only).
 * @return       Acceleration vector, representing d²r/dt².
 */
Matrix AccelHarmonic(Matrix r, Matrix E, int n_max, int m_max);

#endif