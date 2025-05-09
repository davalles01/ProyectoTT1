// $Source$
// --------------------------------------------------------------------------------------------------------
// TimeUpdate_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file TimeUpdate_test.cpp
 *  @brief Test for the TimeUpdate function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include "../include/TimeUpdate.hpp"
#include "../include/matrix.hpp"

void TimeUpdate_test() {
    Matrix P = eye(2);
    Matrix Phi(2,2);
    Phi(1,1) = 1; Phi(1,2) = 1; Phi(2,1) = 0; Phi(2,2) = 1;
    double Qdt = 0.1;

    Matrix expected_P(2,2);
    expected_P(1,1) = 2.1; expected_P(1,2) = 1.1;
    expected_P(2,1) = 1.1; expected_P(2,2) = 1.1;

    Matrix updated_P = TimeUpdate(P,Phi,Qdt);

    assert(equals(updated_P,expected_P));
}