// $Source$
// --------------------------------------------------------------------------------------------------------
// PrecMatrix.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file PrecMatrix.cpp
 *  @brief PrecMatrix function implementation. Precession transformation of equatorial coordinates
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/PrecMatrix.hpp"

Matrix PrecMatrix(double Mjd_1, double Mjd_2){
    
    double T  = (Mjd_1-MJD_J2000)/36525;
    double dT = (Mjd_2-Mjd_1)/36525;

    double zeta  =  ( (2306.2181+(1.39656-0.000139*T)*T) + ((0.30188-0.000344*T)+0.017998*dT)*dT )*dT/Arcs;
    double z =  zeta + ( (0.79280+0.000411*T)+0.000205*dT)*dT*dT/Arcs;
    double theta =  ( (2004.3109-(0.85330+0.000217*T)*T) - ((0.42665+0.000217*T)+0.041833*dT)*dT )*dT/Arcs;

    Matrix aux_1 = R_z(-z);
    Matrix aux_2 = R_y(theta);
    Matrix aux_3 = R_z(-zeta);

    return aux_1 * aux_2 * aux_3;
}