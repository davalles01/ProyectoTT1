// $Header$
// --------------------------------------------------------------------------------------------------------
// DEInteg.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/14
//
/** @file DEInteg.hpp
 *  @brief DEInteg function header.
 *
 *  Integrates a system of ordinary differential equations (ODEs) using the variable-order, 
 *  variable-step multistep method by Shampine & Gordon.
 *
 *  Reference: Shampine, L. F., & Gordon, M. K. (1975). 
 *  Computer Solution of Ordinary Differential Equations: The Initial Value Problem.
 *  Freeman and Company, San Francisco.
 *
 *  @author Daniel Vallés
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _DEINTEG_
#define _DEINTEG_

#include "matrix.hpp"
#include "global.hpp"
#include "constants.hpp"
#include "sign_.hpp"

using namespace constants;
using namespace std;

/**
 * @brief Integrates a system of ordinary differential equations using the Shampine-Gordon method.
 *
 * @param func     Function that computes dy/dt = f(t, y). Should accept (double x, Matrix y) and return Matrix.
 * @param t        Initial time.
 * @param tout     Final time (end of integration interval).
 * @param relerr   Relative error tolerance.
 * @param abserr   Absolute error tolerance.
 * @param n_eqn    Number of differential equations in the system.
 * @param y        On input: initial values of the state vector. On output: solution at time `tout`.
 * @return         State vector at time `tout`.
 */
Matrix DEInteg(Matrix f(double x, Matrix y), double t, double tout, double relerr, double abserr, int n_eqn, Matrix y);

#endif
