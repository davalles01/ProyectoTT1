// $Header$
// --------------------------------------------------------------------------------------------------------
// NutAngles.hpp
// --------------------------------------------------------------------------------------------------------

/** @file NutAngles.hpp
 *  @brief Header for the NutAngles function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

 #ifndef _NUTANGLES_
 #define _NUTANGLES_

 #include "matrix.hpp"

 /**
  * @brief Computes the Nutation in longitude and obliquity
  *
  * @param Mjd_TT MOdified Julian Date (Terrestial time)
  * @return tuple<Matrix&, Matrix&> A tuple containing the nutation angles
  */
 tuple<double, double> NutAngles(double Mjd_TT);

 #endif
