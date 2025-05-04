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

void IERS_interp_test() {
    // Cargar solo las primeras 4 líneas del archivo eop19620101.txt
    eop19620101(4);

    double Mjd_UTC = 37666.5;  // 2 de enero de 1962 a las 12:00 UTC

    auto [x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC] = IERS(eopdata, Mjd_UTC, 'l');

    // Interpolación a mano entre filas 2 y 3
    double x_pole_expected  = (-0.015900 + -0.019000) / 2.0 / Arcs;
    double y_pole_expected  = (0.214100 + 0.215200)  / 2.0 / Arcs;
    double UT1_UTC_expected = (0.0320547 + 0.0315526) / 2.0;
    double LOD_expected     = (0.0016690 + 0.0015820) / 2.0;
    double dpsi_expected    = (0.063979 + 0.063870) / 2.0 / Arcs;
    double deps_expected    = (0.006290 + 0.006515) / 2.0 / Arcs;
    double dx_pole_expected = 0.0;
    double dy_pole_expected = 0.0;
    double TAI_UTC_expected = 2.0;  // El valor no se interpola

    assert(equals(x_pole, x_pole_expected));
    assert(equals(y_pole, y_pole_expected));
    assert(equals(UT1_UTC, UT1_UTC_expected));
    assert(equals(LOD, LOD_expected));
    assert(equals(dpsi, dpsi_expected));
    assert(equals(deps, deps_expected));
    assert(equals(dx_pole, dx_pole_expected));
    assert(equals(dy_pole, dy_pole_expected));
    assert(equals(TAI_UTC, TAI_UTC_expected));

}
