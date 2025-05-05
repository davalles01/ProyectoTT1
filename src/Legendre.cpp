// $Source$
// --------------------------------------------------------------------------------------------------------
// Legendre.cpp
// --------------------------------------------------------------------------------------------------------

/** @file Legendre.cpp
 *  @brief Implementation of the Legendre function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
*/

#include "../include/Legendre.hpp"
#include <cmath>
 
tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi) {

    Matrix &pnm = zeros(n+1,n+1); // Matrix to store the Legendre polynomials
    Matrix &dpnm = zeros(n+1,n+1); // Matrix to store the derivatives
 
    // Initialize first elements
    pnm(1,1) = 1.0;
    dpnm(1,1) = 0.0;
    pnm(2,2) = sqrt(3)*cos(fi);
    dpnm(2,2) = -sqrt(3)*sin(fi);
 
    // Diagonal coefficients
    for (int i = 2; i <= n; i++) {
        pnm(i+1, i+1) = sqrt((2*i + 1) / (2*i)) * cos(fi) * pnm(i, i);
        dpnm(i+1, i+1) = sqrt((2*i + 1) / (2*i)) * (cos(fi) * dpnm(i, i) - sin(fi) * pnm(i, i));
    }

    // Horizontal first step coefficients
    for (int i = 1; i <= n; i++) {
        pnm(i+1,i)= sqrt(2*i+1)*sin(fi)*pnm(i,i);
        dpnm(i+1,i)= sqrt(2*i+1)*((cos(fi)*pnm(i,i))+(sin(fi)*dpnm(i,i)));
    }
    
    // Horizontal second step coefficients
    int j = 0, k = 2;
    while (j <= m) {
        for (int i = k; i <= n; i++) {

            pnm(i+1,j+1)=sqrt((2*i+1)/((i-j)*(i+j)))*((sqrt(2*i-1)*sin(fi)*pnm(i,j+1))
            -(sqrt(((i+j-1)*(i-j-1))/(2*i-3))*pnm(i-1,j+1)));

            dpnm(i+1,j+1)=sqrt((2*i+1)/((i-j)*(i+j)))*((sqrt(2*i-1)*sin(fi)*dpnm(i,j+1))
            +(sqrt(2*i-1)*cos(fi)*pnm(i,j+1))-(sqrt(((i+j-1)*(i-j-1))/(2*i-3))*dpnm(i-1,j+1)));
        }
        j++;
        k++;
    }
 
    return tie(pnm, dpnm);
}
 