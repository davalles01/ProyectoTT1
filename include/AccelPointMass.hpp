// $Header$
// --------------------------------------------------------------------------------------------------------
// AccelPointMass.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file AccelPointMass.hpp
 *  @brief AccelPointMass function declaration, to compute perturbational acceleration.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _ACCELPOINTMASS_
#define _ACCELPOINTMASS_

#include "./matrix.hpp"
#include <cmath>

/**
 * @brief Computes the perturbational acceleration due to a point mass. 
 * @param r Satellite position vector
 * @param s Point mass position vector
 * @param GM Gravitational coefficient of point mass
 * @return Acceleration (a=d^2r/dt^2)
 */
Matrix AccelPointMass(Matrix &r, Matrix &s, double GM);

#endif
