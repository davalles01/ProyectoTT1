// $Source$
// --------------------------------------------------------------------------------------------------------
// MeasUpdate.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file MeasUpdate.cpp
 *  @brief Source file for the MeasUpdate function implementation
 *
 *  Performs a Kalman measurement update for the state vector and its covariance.
 *
 *  This function computes the Kalman gain, updates the state estimate based on the measurement residual,
 *  and adjusts the covariance matrix accordingly. The measurement noise is assumed to be diagonal.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/MeasUpdate.hpp"

tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& prior_x, double z, double g, double s, Matrix& G, Matrix& prior_P, int n){

    int m = 1;
    Matrix Inv_W = zeros(m,m);

    for(int i = 1; i<=m; i++){
        Inv_W(i,i) = s*s;
    }
    
    Matrix &K = prior_P*transpose(G)*inv(G*prior_P*transpose(G) + Inv_W);
    
    Matrix &x = prior_x + K*(z-g);
    
    Matrix &P = (eye(n)-K*G)*prior_P;
    
    return tie(K,x,P);
}