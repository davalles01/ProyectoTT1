// $Source$
// --------------------------------------------------------------------------------------------------------
// TimeUpdate.cpp
// --------------------------------------------------------------------------------------------------------

/** @file TimeUpdate.cpp
 *  @brief Implementation of the TimeUpdate function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/TimeUpdate.hpp"

Matrix TimeUpdate(Matrix P, Matrix Phi, double Qdt){
    return Phi*P*transpose(Phi) + Qdt;
}