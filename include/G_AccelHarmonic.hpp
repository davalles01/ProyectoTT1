// $Header$
// --------------------------------------------------------------------------------------------------------
// G_AccelHarmonic.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file G_AccelHarmonic.hpp
 *  @brief Header file for the G_AccelHarmonic function.
 *
 *  Computes the gradient of the Earth's harmonic gravity field.
 *
 *  This function computes the gradient of the gravitational acceleration vector (∂a/∂r),
 *  derived from a spherical harmonics expansion of the Earth's gravity field, in the
 *  true-of-date reference system.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _G_ACCELHARMONIC_
#define _G_ACCELHARMONIC_

#include "matrix.hpp"
#include "AccelHarmonic.hpp"

/**
 * @brief Computes the gradient of the Earth's harmonic gravity field.
 * 
 *  @param r      Satellite position vector in the true-of-date system
 *  @param U      Transformation matrix from inertial to body-fixed frame (3x3).
 *  @param n_max  Maximum degree of the gravity model.
 *  @param m_max  Maximum order of the gravity model.
 *  @return       Gradient matrix G = ∂a/∂r in the true-of-date system (3x3).
 */
Matrix G_AccelHarmonic(Matrix r, Matrix U, int n_max, int m_max);

#endif