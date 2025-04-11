// $Header$
// --------------------------------------------------------------------------------------------------------
// Cheb3D.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file Cheb3D.hpp
 *  @brief Cheb3D function declaration, to evaluate 3D Chebyshev polynomial approximation.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _CHEB3D_
#define _CHEB3D_

#include "./matrix.hpp"

/**
 * @brief Evaluates a 3D Chebyshev polynomial using Clenshaw's algorithm.
 * 
 * @param t     Time at which to evaluate
 * @param N     Number of coefficients
 * @param Ta    Begin of interval
 * @param Tb    End of interval
 * @param Cx    Coefficients for x-coordinate (1 x N)
 * @param Cy    Coefficients for y-coordinate (1 x N)
 * @param Cz    Coefficients for z-coordinate (1 x N)
 * @return Matrix Approximated position vector [x, y, z]
 */
Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix Cx, Matrix Cy, Matrix Cz);

#endif
