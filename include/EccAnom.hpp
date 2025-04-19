// $Header$
// --------------------------------------------------------------------------------------------------------
// EccAnom.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file EccAnom.hpp
 *  @brief EccAnom function declaration, which computes the eccentric anomaly for elliptic orbits.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _ECCANOM_HPP
#define _ECCANOM_HPP

#include "./matrix.hpp"

/** @brief Computes the eccentric anomaly for elliptic orbits.
 *  @param M Mean anomaly [rad]
 *  @param e Eccentricity of the orbit [0,1]
 *  @return Eccentric anomaly [rad]
 */
double EccAnom(double M, double e);

#endif // ECCANOM_HPP
