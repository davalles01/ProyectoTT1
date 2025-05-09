// $Source$
// --------------------------------------------------------------------------------------------------------
// PoleMatrix.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file PoleMatrix.cpp
 *  @brief PoleMatrix function implementation. Transformation from pseudo Earth-fixed to Earth-fixed coordinates for a given date
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/PoleMatrix.hpp"

Matrix PoleMatrix(double xp, double yp){
    
    Matrix aux_1 = R_y(-xp);
    Matrix aux_2 = R_x(-yp);

    return aux_1*aux_2;
}