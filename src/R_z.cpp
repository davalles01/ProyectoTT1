// $Source$
// --------------------------------------------------------------------------------------------------------
// R_z.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file R_z.cpp
 *  @brief R_z function implementation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/R_z.hpp"
#include <cmath>

Matrix R_z(double angle) {
    double C = cos(angle);
    double S = sin(angle);
    Matrix rotmat(3, 3);

    rotmat(1,1) =    C;  rotmat(1,2) =   S;  rotmat(1,3) = 0.0;
    rotmat(2,1) = -1.0*S; rotmat(2,2) =  C;  rotmat(2,3) = 0.0;
    rotmat(3,1) =  0.0;  rotmat(3,2) = 0.0;  rotmat(3,3) = 1.0;

    return rotmat;
}
