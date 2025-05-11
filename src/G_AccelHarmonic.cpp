// $Source$
// --------------------------------------------------------------------------------------------------------
// G_AccelHarmonic.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file G_AccelHarmonic.cpp
 *  @brief Source file for the G_AccelHarmonic function.
 *
 *  Computes the gradient of the Earth's harmonic gravity field.
 *
 *  This function computes the gradient of the gravitational acceleration vector (∂a/∂r),
 *  derived from a spherical harmonics expansion of the Earth's gravity field, in the
 *  true-of-date reference system.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/G_AccelHarmonic.hpp"

Matrix G_AccelHarmonic(Matrix r, Matrix U, int n_max, int m_max){

    double d = 1.0;   

    Matrix G = zeros(3,3);
    Matrix dr;
    Matrix da;

    for(int i = 1; i <= 3; i++){
        dr = zeros(3);
        dr(i) = d;
        
        Matrix acc_plus = AccelHarmonic(r+dr/2, U, n_max, m_max);
        Matrix acc_minus = AccelHarmonic(r-dr/2, U, n_max, m_max);
        da = acc_plus - acc_minus;
        
        assign_column(G,i,da/d);
    }

    return G;
}