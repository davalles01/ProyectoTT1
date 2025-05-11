// $Source$
// --------------------------------------------------------------------------------------------------------
// It1_tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file It1_tests.cpp
 *  @brief Tests for all iteration 1 functions
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include "../include/SAT_Const.hpp"
#include "../include/matrix.hpp"
#include "../include/constants.hpp"
#include "../include/global.hpp"

#include "../include/AccelPointMass.hpp"
#include "../include/Cheb3D.hpp"
#include "../include/EccAnom.hpp"
#include "../include/Frac.hpp"
#include "../include/MeanObliquity.hpp"
#include "../include/Mjday.hpp"
#include "../include/Mjday_TDB.hpp"
#include "../include/Position.hpp"
#include "../include/R_x.hpp"
#include "../include/R_y.hpp"
#include "../include/R_z.hpp"
#include "../include/sign_.hpp"
#include "../include/timediff.hpp"
#include "../include/AzElPa.hpp"
#include "../include/IERS.hpp"
#include "../include/Legendre.hpp"
#include "../include/NutAngles.hpp"
#include "../include/TimeUpdate.hpp"

using namespace std;
using namespace consts;
using namespace constants;

bool equals(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

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

void Cheb3D_test(){
    
    int N = 3;
    double Ta = 0.0;
    double Tb = 10.0;
    double t = 3.0;
    
    Matrix Cx(3);
    Cx(1) = 1.0;  Cx(2) = 0.5;   Cx(3) = -0.2;
    
    Matrix Cy(3);
    Cy(1) = 0.0;  Cy(2) = 1.0;   Cy(3) = 0.3;
    
    Matrix Cz(3);
    Cz(1) = 2.0;  Cz(2) = -0.5;  Cz(3) = 0.1;
    
    Matrix expected(3);
    expected(1) = 0.936; expected(2) = -0.604; expected(3) = 2.132;

    Matrix result = Cheb3D(t, N, Ta, Tb, Cx, Cy, Cz);

    assert(equals(expected, result));

}

void EccAnom_test(){
    
    double M1 = pi/3;
    double e1 = 0.0;

    double result1 = EccAnom(M1,e1);
    double expected1 = M1;

    assert(equals(expected1, result1));

    double M2 = 1.0;
    double e2 = 0.6;

    double result2 = EccAnom(M2,e2);
    double expected2 = 1.599748548227530;

    assert(equals(expected2, result2));
}

void Frac_test() {
    // Test cases
    assert(equals(Frac(3.14), 0.14));
    assert(equals(Frac(-2.75), 0.25));
    assert(equals(Frac(0.0), 0.0));
    assert(equals(Frac(5.0), 0.0));
    assert(equals(Frac(-0.1), 0.9));
}

void MeanObliquity_test() {
    double Mjd_TT = MJD_J2000;  // Epoch J2000.0

    double result = MeanObliquity(Mjd_TT);

    // Valor esperado en radianes: 84381.448 arcsec = 0.409092804 rad
    double expected = 0.409092804;

    assert(std::abs(result - expected) < 1e-4);
}

void Mjday_test() {
    // Test input: 2024, 3, 15, 12, 0, 0 (March 15, 2024, at 12:00:00)
    int year = 2024;
    int month = 3;
    int day = 15;
    int hour = 12;
    int minute = 0;
    double second = 0.0;
    
    double expected_MJD = 6.038450000000000e+04;  // Expected MJD for this date

    double result = Mjday(year, month, day, hour, minute, second);

    // Comprobar que el resultado está dentro de un margen de error
    assert(std::abs(result - expected_MJD) < 1e-10);
}

void Mjday_TDB_test() {
    double Mjd_TT = 60384.0;       // 2024-03-15 12:00:00 TT
    double Mjd_TDB = Mjday_TDB(Mjd_TT);

    // Expected value computed from MATLAB
    double expected = 6.038400000001785e+04;
    double tolerance = 1e-10;

    assert(std::abs(Mjd_TDB - expected) < tolerance);
}

void Position_test() {
    // Input values: longitude, latitude in radians, altitude in meters
    double lon = 1.0;           // ≈ 57.3°
    double lat = 0.5;           // ≈ 28.6°
    double h = 1000.0;          // 1 km altitude

    Matrix result = Position(lon, lat, h);
    
    // Obtenidos en MATLAB
    Matrix expected(3);
    expected(1) = 3.027060239398717;
    expected(2) = 4.714366999835280;
    expected(3) = 3.040190332390430;

    expected = expected * 1.0e+6;

    assert(abs(result(1) - expected(1)) < 1e-5);
    assert(abs(result(2) - expected(2)) < 1e-5);
    assert(abs(result(3) - expected(3)) < 1e-5);
}

void R_x_test(){
    
    Matrix R_x1(3,3);
    R_x1(1,1) = 1.0; R_x1(1,2) = 0.0; R_x1(1,3) = 0.0;
    R_x1(2,1) = 0.0; R_x1(2,2) = -0.416147; R_x1(2,3) = 0.909297;
    R_x1(3,1) = 0.0; R_x1(3,2) = -0.909297; R_x1(3,3) = -0.416147;

    Matrix R_x2(3,3);
    R_x2(1,1) = 1.0; R_x2(1,2) = 0.0; R_x2(1,3) = 0.0;
    R_x2(2,1) = 0.0; R_x2(2,2) = 0.468517; R_x2(2,3) = 0.883455;
    R_x2(3,1) = 0.0; R_x2(3,2) = -0.883455; R_x2(3,3) = 0.468517;

    assert(equals(R_x(2),R_x1));
    assert(equals(R_x(-5.2),R_x2));

}

void R_y_test() {
    double angle = pi / 4;  // 45 degrees
    Matrix R = R_y(angle);

    Matrix expected(3,3);
    expected(1,1) =   0.707106781186548;  expected(1,2) = 0.0;  expected(1,3) = -0.707106781186547;
    expected(2,1) = 0.0;  expected(2,2) = 1.0;  expected(2,3) = 0.0;
    expected(3,1) = 0.707106781186547;  expected(3,2) = 0.0;  expected(3,3) = 0.707106781186548;

    assert(equals(R,expected));
}

void R_z_test() {
    double angle = pi / 4;  // 45 degrees
    Matrix R = R_z(angle);

    // Values obtained from MATLAB
    Matrix expected(3,3);
    expected(1,1) =  0.707106781186548; expected(1,2) =  0.707106781186547; expected(1,3) = 0.0;
    expected(2,1) = -0.707106781186547; expected(2,2) =  0.707106781186548; expected(2,3) = 0.0;
    expected(3,1) =  0.0;               expected(3,2) =  0.0;               expected(3,3) = 1.0;

    assert(equals(R, expected));
}

void sign__test() {
    assert(sign_(5.0, 3.0) == 5.0);     // both positive
    assert(sign_(-5.0, 3.0) == 5.0);    // a negative, b positive
    assert(sign_(5.0, -3.0) == -5.0);   // a positive, b negative
    assert(sign_(-5.0, -3.0) == -5.0);  // both negative
    assert(sign_(0.0, -1.0) == -0.0);   // zero with negative sign
    assert(sign_(0.0, 1.0) == 0.0);     // zero with positive sign
}

void timediff_test() {
    double UT1_UTC = 0.3341;
    double TAI_UTC = 37.0;

    auto [UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC] = timediff(UT1_UTC, TAI_UTC);

    assert(std::abs(UT1_TAI - (-36.6659)) < 1e-10);
    assert(std::abs(UTC_GPS - (-18.0)) < 1e-10);
    assert(std::abs(UT1_GPS - (-17.6659)) < 1e-10);
    assert(std::abs(TT_UTC - 69.184) < 1e-10);
    assert(std::abs(GPS_UTC - 18.0) < 1e-10);
}

void AzElPa_test() {
    Matrix s(3);
    s(1) = 1.0;  // East component
    s(2) = 1.0;  // North component
    s(3) = 1.0;  // Zenith component

    double Az, El;
    Matrix dAds(3), dEds(3);

    tie(Az, El, dAds, dEds) = AzElPa(s);

    // Expected values based on the input (1,1,1)
    assert(fabs(Az - 0.785398163397448) < 1e-7);
    assert(fabs(El - 0.615479708670387) < 1e-7);
    assert(fabs(dAds(1) - 0.5) < 1e-7);
    assert(fabs(dAds(2) + 0.5) < 1e-7);
    assert(fabs(dAds(3) - 0.0) < 1e-7);
    assert(fabs(dEds(1) + 0.235702260395516) < 1e-7);
    assert(fabs(dEds(2) + 0.235702260395516) < 1e-7);
    assert(fabs(dEds(3) - 0.471404520791032) < 1e-7);
}

void IERS_test() {
    
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

void Legendre_test() {
    // Parámetros de entrada
    int n = 5;
    int m = 3;
    double fi = M_PI / 4;

    // Ejecutar la función Legendre
    auto [pnm, dpnm] = Legendre(n, m, fi);

   // Matriz esperada pnm (6x6)
   Matrix expected_pnm = zeros(6, 6);
   expected_pnm(1,1) = 1.00000;
   
   expected_pnm(2,1) = 1.22474; expected_pnm(2,2) = 1.22474;
   
   expected_pnm(3,1) = 0.559017; expected_pnm(3,2) = 1.93649; expected_pnm(3,3) = 0.968246;
   
   expected_pnm(4,1) = -0.467707; expected_pnm(4,2) = 1.71847; expected_pnm(4,3) = 1.81142; expected_pnm(4,4) = 0.73951;
   
   expected_pnm(5,1) = -1.21875; expected_pnm(5,2) = 0.592927; expected_pnm(5,3) = 2.09631; expected_pnm(5,4) = 1.56874; expected_pnm(5,5) = 0.554632;
   
   expected_pnm(6,1) = -1.24589; expected_pnm(6,2) = -0.851527; expected_pnm(6,3) = 1.50195; expected_pnm(6,4) = 2.14609; expected_pnm(6,5) = 1.30073; expected_pnm(6,6) = 0.411326;
   
   // Matriz esperada dpnm (6x6)
   Matrix expected_dpnm = zeros(6, 6);
   expected_dpnm(2,1) = 1.22474; expected_dpnm(2,2) = -1.22474;
   
   expected_dpnm(3,1) = 3.3541; expected_dpnm(3,2) = 7.4476e-16; expected_dpnm(3,3) = -1.93649;
   
   expected_dpnm(4,1) = 4.20936; expected_dpnm(4,2) = 4.00975; expected_dpnm(4,3) = -1.81142; expected_dpnm(4,4) = -2.21853;
   
   expected_dpnm(5,1) = 1.875; expected_dpnm(5,2) = 8.30098; expected_dpnm(5,3) = 1.67705; expected_dpnm(5,4) = -3.13748; expected_dpnm(5,5) = -2.21853;
   
   expected_dpnm(6,1) = -3.29795; expected_dpnm(6,2) = 8.79911; expected_dpnm(6,3) = 7.50976; expected_dpnm(6,4) = -0.919754; expected_dpnm(6,5) = -3.90219; expected_dpnm(6,6) = -2.05663;
   
   assert(equals(pnm, expected_pnm));
   assert(equals(dpnm, expected_dpnm));
}

void NutAngles_test() {
    // Input
    double Mjd_TT = 51544.5;

    // Call function
    auto [dpsi, deps] = NutAngles(Mjd_TT);

    // Expected values from MATLAB
    double expected_dpsi = -6.750247617532479e-05;
    double expected_deps = -2.799221238377013e-05;

    // Compare with tolerance
    assert(equals(dpsi, expected_dpsi));
    assert(equals(deps, expected_deps));
}

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

void It1_tests(){
    
    AccelPointMass_test();
    Cheb3D_test();
    EccAnom_test();
    Frac_test();
    MeanObliquity_test();
    Mjday_test();
    Mjday_TDB_test();
    Position_test();
    R_x_test();
    R_y_test();
    R_z_test();
    sign__test();
    timediff_test();
    AzElPa_test();
    IERS_test();
    IERS_interp_test();
    Legendre_test();
    NutAngles_test();
    TimeUpdate_test();

    cout << "All Iteration 1 tests passed successfully.\n";
}