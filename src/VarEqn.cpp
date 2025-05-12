// $Source$
// --------------------------------------------------------------------------------------------------------
// VarEqn.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/12
//
/** @file VarEqn.cpp
 *  @brief Header file for the VarEqn function. Computes the time derivative of the combined state vector and state transition matrix
 *  for an Earth-orbiting satellite. The state transition matrix describes the sensitivity of the 
 *  state with respect to initial conditions, which is fundamental in orbit determination and 
 *  estimation theory.
 *
 *  @author Daniel Vallés Belloso
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/VarEqn.hpp"

Matrix VarEqn(double x, Matrix yPhi){

    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,AuxParam.Mjd_UTC,'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    double Mjd_UT1 = AuxParam.Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;

    Matrix P = PrecMatrix(MJD_J2000,AuxParam.Mjd_TT + x/86400.0);
    Matrix N = NutMatrix(AuxParam.Mjd_TT + x/86400.0);
    Matrix T = N * P;
    Matrix GHA_T = GHAMatrix(Mjd_UT1) * T;
    Matrix E = PoleMatrix(x_pole,y_pole) * GHA_T;

    Matrix r = extract_vector(yPhi, 1, 3); 
    Matrix v = extract_vector(yPhi, 4, 6);
    Matrix Phi = zeros(6,6);

    for(int j = 1; j<= 6; j++){
        assign_column(Phi,j,extract_vector(yPhi,6*j+1,6*j+6));
    }

    Matrix a = AccelHarmonic ( r, E, AuxParam.n, AuxParam.m );
    Matrix G = G_AccelHarmonic ( r, E, AuxParam.n, AuxParam.m );

    Matrix yPhip = zeros(42);
    Matrix dfdy = zeros(6,6);

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            dfdy(i, j)       = 0.0;         // dv/dr(i,j)
            dfdy(i + 3, j)   = G(i, j);     // da/dr(i,j)
            if (i == j) {
                dfdy(i, j + 3) = 1.0;       // dv/dv(i,j)
            } else {
                dfdy(i, j + 3) = 0.0;
            }
            dfdy(i + 3, j + 3) = 0.0;       // da/dv(i,j)
        }
    }    

    Matrix Phip = dfdy*Phi;

    for (int i = 1; i <= 3; i++) {
        yPhip(i)     = v(i);   // dr/dt(i)
        yPhip(i + 3) = a(i);   // dv/dt(i)
    }
    
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            yPhip(6*j + i) = Phip(i, j); // dPhi/dt(i,j), almacenamiento columna a columna
        }
    }
    
    return yPhip;
}