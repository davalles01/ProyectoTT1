// $Source$
// --------------------------------------------------------------------------------------------------------
// gast.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file gast.cpp
 *  @brief Source file for the gast function implementation
 *
 *  Computes Greenwich Apparent Sidereal Time
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/gast.hpp"
#include <cmath>

double gast(double Mjd_UT1){
    return fmod(gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), 2*pi);
}