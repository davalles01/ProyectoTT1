// $Source$
// --------------------------------------------------------------------------------------------------------
// IERS_test.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/30
//
/** @file IERS_test.cpp
 *  @brief Test for the IERS function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include "../include/IERS.hpp"
#include "../include/global.hpp"
#include "../include/SAT_Const.hpp"

using namespace consts;

bool equals(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

void IERS_test() {
    // Cargar solo las primeras 4 líneas del archivo eop19620101.txt
    eop19620101(4);

    double Mjd_UTC = 37666.0;  // 2 de enero de 1972

    auto [x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC] = IERS(eopdata, Mjd_UTC, 'n');

    // Comprobación contra valores esperados (convertidos a radianes)
    assert(equals(x_pole, -0.015900 / Arcs));
    assert(equals(y_pole,  0.214100 / Arcs));
    assert(equals(UT1_UTC, 0.0320547));
    assert(equals(LOD,     0.0016690));
    assert(equals(dpsi,    0.063979 / Arcs));
    assert(equals(deps,    0.006290 / Arcs));
    assert(equals(dx_pole, 0.000000 / Arcs));
    assert(equals(dy_pole, 0.000000 / Arcs));
    assert(equals(TAI_UTC, 2.0));

}
