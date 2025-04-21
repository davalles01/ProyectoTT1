// $Source$
// --------------------------------------------------------------------------------------------------------
// R_y.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file R_y.cpp
 *  @brief R_y function implementation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/R_y.hpp"
#include <cmath>

Matrix R_y(double angle) {

  double C = cos(angle);
  double S = sin(angle);
  Matrix rotmat(3, 3);

  rotmat(1,1) =   C;  rotmat(1,2) = 0.0;  rotmat(1,3) = -1.0 * S;
  rotmat(2,1) = 0.0;  rotmat(2,2) = 1.0;  rotmat(2,3) =      0.0;
  rotmat(3,1) =   S;  rotmat(3,2) = 0.0;  rotmat(3,3) =      C;

  return rotmat;
}
