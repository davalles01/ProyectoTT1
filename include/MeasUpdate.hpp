// $Header$
// --------------------------------------------------------------------------------------------------------
// MeasUpdate.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file MeasUpdate.hpp
 *  @brief Header file for the MeasUpdate function.
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

#ifndef _MEASUPDATE_
#define _MEASUPDATE_

#include "matrix.hpp"

/**
 * @brief  Performs a Kalman measurement update for the state vector and its covariance.
 * 
 *  @param  x  Prior state estimate (n×1)
 *  @param  z  Measurement 
 *  @param  g  Expected measurement from the current state
 *  @param  s  Standard deviation of each measurement
 *  @param  G  Measurement matrix (m×n)
 *  @param  P  Prior covariance matrix (n×n)
 *  @param  n  Dimension of the state vector
 *  @return tuple<Matrix, Matrix, Matrix> K  Kalman gain matrix (n×m), x  Updated state estimate (n×1), P  Updated covariance matrix (n×n)
 */
tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& prior_x, double z, double g, double s, Matrix& G, Matrix& prior_P, int n);

#endif 
