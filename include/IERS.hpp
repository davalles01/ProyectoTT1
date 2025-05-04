// $Header$
// --------------------------------------------------------------------------------------------------------
// IERS.hpp
// --------------------------------------------------------------------------------------------------------

/** @file IERS.hpp
 *  @brief Header for the IERS function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */

 #ifndef _IERS_
 #define _IERS_
 
 #include "matrix.hpp"
 
 /**
  * @brief Management of IERS time and polar motion data.
  *
  * @param eop    Earth Orientation Parameters (input data matrix).
  * @param Mjd_UTC    Modified Julian Date (input).
  * @param interp    Interpolation option ('l' for linear, 'n' for none) (default = 'n').
  * @return tuple<double,...,double> A tuple with the following data: x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC
  */
 tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp = 'n');
 
 #endif
 