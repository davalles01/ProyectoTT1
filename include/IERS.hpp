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
  * 
  * @param x_pole    Polar motion in the x direction [rad].
  * @param y_pole    Polar motion in the y direction [rad].
  * @param UT1_UTC    UT1-UTC time difference [s].
  * @param LOD    Length of day [s].
  * @param dpsi    Longitudinal displacement of the pole [rad].
  * @param deps    Latitudinal displacement of the pole [rad].
  * @param dx_pole    Derivative of x_pole with respect to time [rad/day].
  * @param dy_pole    Derivative of y_pole with respect to time [rad/day].
  * @param TAI_UTC    TAI-UTC time difference [s].
  */
 void IERS(Matrix& eop, double Mjd_UTC, char interp = 'n',
           double& x_pole, double& y_pole, double& UT1_UTC, double& LOD, 
           double& dpsi, double& deps, double& dx_pole, double& dy_pole, double& TAI_UTC);
 
 #endif
 