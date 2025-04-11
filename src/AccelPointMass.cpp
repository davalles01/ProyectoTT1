// $Source$
// --------------------------------------------------------------------------------------------------------
// AccelPointMass.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file AccelPointMass.cpp
 *  @brief AccelPointMass function implementation, to compute perturbational acceleration.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AccelPointMass.hpp"

Matrix AccelPointMass(Matrix &r, Matrix &s, double GM){

    // Relative position vector of satellite w.r.t. point mass 
    Matrix d = r - s;

    // Acceleration
    Matrix a = ( d/(pow(norm(d),3)) + s/(pow(norm(s),3)) ) * (-GM);

    return a;
}