// $Source$
// --------------------------------------------------------------------------------------------------------
// GHAMatrix.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file GHAMatrix.cpp
 *  @brief Source file for the GHAMatrix function implementation
 *
 *  Computes the transformation matrix from the true equator and equinox system 
 *  to the Earth equator and Greenwich meridian system using the Greenwich Hour Angle.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/GHAMatrix.hpp"

Matrix GHAMatrix(double Mjd_UT1){
    return R_z(gast(Mjd_UT1));
}