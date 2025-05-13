// $Header$
// --------------------------------------------------------------------------------------------------------
// AccelHarmonic.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file AccelHarmonic.cpp
 *  @brief AccelHarmonic function implementation. Computes the acceleration due to the harmonic gravity field of the central body
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AccelHarmonic.hpp"
#include <cmath>

Matrix AccelHarmonic(Matrix r, Matrix E, int n_max, int m_max){
    
    double r_ref = 6378.1363e3;   
    double gm    = 398600.4415e9; 

    Matrix r_bf_aux = E * transpose(r); 
    Matrix r_bf = transpose(r_bf_aux); 

    double d = norm(r_bf);
    double latgc = asin(r_bf(3)/d);
    double lon = atan2(r_bf(2),r_bf(1));

    auto [pnm, dpnm] = Legendre(n_max,m_max,latgc);

    double dUdr = 0.0;
    double dUdlatgc = 0.0;
    double dUdlon = 0.0;
    double q3 = 0.0; 
    double q2 = 0.0; 
    double q1 = 0.0;

    for (int n = 0; n <= n_max; n++) {
        double b1 = (-gm / (d * d)) * pow(r_ref / d, n) * (n + 1);
        double b2 =  (gm / d) * pow(r_ref / d, n);
        double b3 =  (gm / d) * pow(r_ref / d, n);
    
        for (int m = 0; m <= m_max; m++) {
            double cosmlon = cos(m * lon);
            double sinmlon = sin(m * lon);
            double C = Cnm(n + 1, m + 1);  
            double S = Snm(n + 1, m + 1);
            double P = pnm(n + 1, m + 1);
            double dP = dpnm(n + 1, m + 1);
    
            q1 += P * (C * cosmlon + S * sinmlon);
            q2 += dP * (C * cosmlon + S * sinmlon);
            q3 += m * P * (S * cosmlon - C * sinmlon);
        }
    
        dUdr     += q1 * b1;
        dUdlatgc += q2 * b2;
        dUdlon   += q3 * b3;
    
        q1 = 0.0;
        q2 = 0.0;
        q3 = 0.0;
    }

    double r2xy = pow(r_bf(1),2) + pow(r_bf(2),2);
    
    Matrix a_bf(3,1);
    a_bf(1,1) = (1.0/d*dUdr-r_bf(3)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(1)-(1/r2xy*dUdlon)*r_bf(2);
    a_bf(2,1) = (1.0/d*dUdr-r_bf(3)/(pow(d,2)*sqrt(r2xy))*dUdlatgc)*r_bf(2)+(1/r2xy*dUdlon)*r_bf(1);
    a_bf(3,1) =  1.0/d*dUdr*r_bf(3)+sqrt(r2xy)/pow(d,2)*dUdlatgc;

    return transpose(transpose(E)*a_bf); // Lo trasponemos para devolver un vector fila, en lugar de columna
}