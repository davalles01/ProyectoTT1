// $Source$
// --------------------------------------------------------------------------------------------------------
// EqnEquinox.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file EqnEquinox.cpp
 *  @brief EqnEquinox function implementation, which computes the equation of the equinoxe
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/EqnEquinox.hpp"

double EqnEquinox(double Mjd_TT){
    auto[dpsi,deps] = NutAngles(Mjd_TT);

    return dpsi*cos(MeanObliquity(Mjd_TT));
}
