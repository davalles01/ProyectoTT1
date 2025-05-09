// $Source$
// --------------------------------------------------------------------------------------------------------
// LTC.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file LTC.cpp
 *  @brief LTC function imoplementation. Transformation from Greenwich meridian system to local tangent coordinates
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/LTC.hpp"

Matrix LTC(double lon, double lat){

    Matrix MRy = R_y(-1.0*lat);
    Matrix MRz = R_z(lon);

    Matrix M = MRy * MRz;

    for(int j = 1; j <= 3; j++){
        double aux = M(1,j);

        M(1,j)=M(2,j); M(2,j)=M(3,j);

        M(3,j)= aux;
    }

    return M;
}
