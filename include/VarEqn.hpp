// $Header$
// --------------------------------------------------------------------------------------------------------
// VarEqn.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/12
//
/** @file VarEqn.hpp
 *  @brief Header file for the VarEqn function. Computes the time derivative of the combined state vector and state transition matrix
 *  for an Earth-orbiting satellite. The state transition matrix describes the sensitivity of the 
 *  state with respect to initial conditions, which is fundamental in orbit determination and 
 *  estimation theory.
 *
 *  @author Daniel Vallés Belloso
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _VAREQN_
#define _VAREQN_

#include "matrix.hpp"
#include "global.hpp"
#include "IERS.hpp"
#include "timediff.hpp"
#include "AccelHarmonic.hpp"
#include "G_AccelHarmonic.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "PrecMatrix.hpp"
#include "GHAMatrix.hpp"
#include "SAT_Const.hpp"

using namespace consts;

/**
 * @brief Computes the time derivative of the combined state vector and state transition matrix
 *  for an Earth-orbiting satellite
 * 
 * @param x       Time since epoch in seconds.
 * @param yPhi    A (6+36)x1 matrix containing the satellite's state vector (position and velocity) followed by the 6x6 state transition matrix stored column-wise.
 * @return        A (6+36)x1 matrix representing the time derivative of the state and the transition matrix.
 */

Matrix VarEqn(double x, Matrix yPhi);

#endif