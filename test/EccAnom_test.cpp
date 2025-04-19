// $Source$
// --------------------------------------------------------------------------------------------------------
// EccAnom.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file EccAnom.cpp
 *  @brief Test for the EccAnom function
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/EccAnom.hpp"
#include "../include/constants.hpp"
#include <assert.h>

using namespace constants;

/** @brief EccAnom test */
void EccAnom_test(){
    
    double M1 = pi/3;
    double e1 = 0.0;

    double result1 = EccAnom(M1,e1);
    double expected1 = M1;

    assert(equals(expected1, result1));

    double M2 = 1.0;
    double e2 = 0.6;

    double result2 = EccAnom(M2,e2);
    double expected2 = 1.5997;

    assert(equals(expected2, result2));
}