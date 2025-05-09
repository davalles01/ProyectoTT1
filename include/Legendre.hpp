// $Header$
// --------------------------------------------------------------------------------------------------------
// Legendre.hpp
// --------------------------------------------------------------------------------------------------------

/** @file Legendre.hpp
 *  @brief Header for the Legendre function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

 #ifndef _LEGENDRE_
 #define _LEGENDRE_
 
 #include "matrix.hpp"
 
 using std::tuple;
 
 /**
  * @brief Computes the Legendre polynomials and their derivatives.
  *
  * @param n      Maximum degree.
  * @param m      Maximum order.
  * @param fi     Geocentric latitude [rad].
  * @return tuple<Matrix&, Matrix&> A tuple containing matrices pnm and dpnm of size (n+1)x(m+1).
  */
 tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi);
 
 #endif
 