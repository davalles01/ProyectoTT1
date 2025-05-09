// $Source$
// --------------------------------------------------------------------------------------------------------
// NutMatrix.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file NutMatrix.cpp
 *  @brief NutMatrix function implementation. Transformation from mean to true equator and equinox
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/NutMatrix.hpp"

Matrix NutMatrix(double Mjd_TT){

    double eps = MeanObliquity (Mjd_TT);

    auto [dpsi, deps] = NutAngles (Mjd_TT);

    Matrix aux_1 = R_x(-eps-deps);
    Matrix aux_2 = R_z(-dpsi);
    Matrix aux_3 = R_x(+eps);

    return aux_1*aux_2*aux_3;
}