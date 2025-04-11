// $Source$
// --------------------------------------------------------------------------------------------------------
// AccelPointMass_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file AccelPointMass_test.cpp
 *  @brief Test for the AccelPointMass function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/AccelPointMass.hpp"
#include <assert.h>

/** @brief AccelPointMass test */
void AccelPointMass_test(){
    
    Matrix r(3);
    r(1) = 7000000.0; r(2) = 0.0; r(3) = 0.0;

    Matrix s(3);
    s(1) = 6371000.0; s(2) = 0.0; s(3) = 0.0;

    double GM = 3.986e14;

    Matrix result(3);
    result(1) = -1017.3; result(2) = 0.0; result(3) = 0.0;

    assert(equals(AccelPointMass(r,s,GM), result));

}