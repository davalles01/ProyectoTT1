// $Header$
// --------------------------------------------------------------------------------------------------------
// TimeUpdate.hpp
// --------------------------------------------------------------------------------------------------------

/** @file TimeUpdate.hpp
 *  @brief Header for the TimeUpdate function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _TIMEUPDATE_
#define _TIMEUPDATE_

#include "matrix.hpp"

/**
 * @brief Performs the time update (prediction) step for the error covariance matrix in a Kalman filter.
 *
 * @param P      Covariance matrix.
 * @param Phi    State transition matrix.
 * @param Qdt    Process noise scalar (default = 0.0)
 * @return       Updated covariance matrix
 */
Matrix TimeUpdate(Matrix P, Matrix Phi, double Qdt = 0.0);

#endif