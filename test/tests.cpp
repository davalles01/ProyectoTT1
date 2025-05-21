// $Source$
// --------------------------------------------------------------------------------------------------------
// tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file tests.cpp
 *  @brief Tests for all functions
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include <iostream>
#include "../include/SAT_Const.hpp"
#include "../include/matrix.hpp"
#include "../include/constants.hpp"
#include "../include/global.hpp"

/* --------------- ITERATION 1 FUNCTIONS' HEADERS --------------- */

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

/* --------------- ITERATION 2 FUNCTIONS' HEADERS --------------- */

#include "../include/EqnEquinox.hpp"
#include "../include/LTC.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/gmst.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/JPL_Eph_DE430.hpp"

/* --------------- ITERATION 3 FUNCTIONS' HEADERS --------------- */

#include "../include/gast.hpp"
#include "../include/MeasUpdate.hpp"
#include "../include/G_AccelHarmonic.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/Accel.hpp"
#include "../include/VarEqn.hpp"

/* --------------- ITERATION 4 FUNCTIONS' HEADERS --------------- */

#include "../include/DEInteg.hpp"

using namespace std;
using namespace consts;
using namespace constants;

/* --------------- AUXILIARY FUNCTIONS --------------- */

bool equals(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

/* --------------- ITERATION 0 FUNCTIONS' TESTS --------------- */



/* --------------- ITERATION 1 FUNCTIONS' TESTS --------------- */

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
    int year = 1995;
    int month = 01;
    int day = 29;
    int hour = 02;
    int minute = 38;
    int second = 49;
    
    double expected_MJD = 49746.110289352;  // Expected MJD for this date

    double result = Mjday(year, month, day, hour, minute, second);

    // Comprobar que el resultado está dentro de un margen de error
    assert(std::abs(result - expected_MJD) < 1e-10);
}

void Mjday_test2() {
    // Test input: 2024, 3, 15, 12, 0, 0 (March 15, 2024, at 12:00:00)
    int year = 2024;
    int month = 3;
    int day = 15;
    int hour = 12;
    int minute = 0;
    int second = 0;
    
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
    
    double lat = Rad*21.5748;
	double lon = Rad*(-158.2706); 
	double alt = 300.20;          

    Matrix result = Position(lon, lat, alt);
    
    // Obtenidos en MATLAB
    Matrix expected(3);
    expected(1) = -5512567.840036068111658;
    expected(2) = -2196994.446669333148748;
    expected(3) = 2330804.966146887280047;

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

/* --------------- ITERATION 2 FUNCTIONS' TESTS --------------- */

void EqnEquinox_test() {
    
    double Mjd_TT = 58000.0; // Corresponde al 14 de Mayo de 2017

    double expected_EqE = -4.315831508180012e-05;

    double EqE = EqnEquinox(Mjd_TT);

    assert(std::abs(EqE - expected_EqE) < 1e-12);
}

void LTC_test(){

    double lon = 0;
    double lat = 0.898441393719869;
    
    Matrix expected_M(3,3);
    expected_M(1,1) = 0.0; expected_M(1,2) = 1.0; expected_M(1,3) = 0.0;
    expected_M(2,1) = -0.782357113369766; expected_M(2,2) = 0.0; expected_M(2,3) = 0.622830110993140;
    expected_M(3,1) = 0.622830110993140; expected_M(3,2) = 0.0; expected_M(3,3) = 0.782357113369766;

    Matrix M = LTC(lon,lat);

    assert(equals(M,expected_M));

}

void NutMatrix_test(){

    double Mjd_TT = 58000.0; // Corresponde al 14 de Mayo de 2017

    Matrix expected_NutMat(3,3);
    expected_NutMat(1,1) =  0.999999998893660;  expected_NutMat(1,2) =  0.000043158315066;  expected_NutMat(1,3) =  0.000018709362925;
    expected_NutMat(2,1) = -0.000043158945113;  expected_NutMat(2,2) =  0.999999998501602;  expected_NutMat(2,3) =  0.000033676422804;
    expected_NutMat(3,1) = -0.000018707909479;  expected_NutMat(3,2) = -0.000033677230243;  expected_NutMat(3,3) =  0.999999999257929;

    Matrix NutMat = NutMatrix(Mjd_TT);

    assert(equals(NutMat, expected_NutMat));

}

void PoleMatrix_test(){

    double xp = 0.1 * M_PI / 180 / 3600;
    double yp = -0.2 * M_PI / 180 / 3600;

    Matrix expected_PoleMat(3,3);
    expected_PoleMat(1,1) =  0.999999999999882;  expected_PoleMat(1,2) = -0.000000000000470;  expected_PoleMat(1,3) =  0.000000484813681;
    expected_PoleMat(2,1) =  0.000000000000000;  expected_PoleMat(2,2) =  0.999999999999530;  expected_PoleMat(2,3) =  0.000000969627362;
    expected_PoleMat(3,1) = -0.000000484813681;  expected_PoleMat(3,2) = -0.000000969627362;  expected_PoleMat(3,3) =  0.999999999999410;

    Matrix PoleMat = PoleMatrix(xp,yp);

    assert(equals(PoleMat, expected_PoleMat));

}

void PrecMatrix_test(){

    double Mjd_1 = 51544.5;
    double Mjd_2 = 58000.0;

    Matrix expected_PrecMat(3,3);
    expected_PrecMat(1,1) =  0.999990714344930;  expected_PrecMat(1,2) = -0.003952453738599;  expected_PrecMat(1,3) = -0.001717362326850;
    expected_PrecMat(2,1) =  0.003952453738422;  expected_PrecMat(2,2) =  0.999992189018458;  expected_PrecMat(2,3) = -0.000003394016435;
    expected_PrecMat(3,1) =  0.001717362327258;  expected_PrecMat(3,2) = -0.000003393810230;  expected_PrecMat(3,3) =  0.999998525326472;


    Matrix PrecMat = PrecMatrix(Mjd_1,Mjd_2);

    assert(equals(PrecMat, expected_PrecMat));

}

void gmst_test(){

    double Mjd_UT1 = 51544.5;

    double gmstime = gmst(Mjd_UT1);
    double expected_gmstime = 4.894961212823057;
    
    assert(std::abs(gmstime - expected_gmstime) < 1e-12);
}

void AccelHarmonic_test(){

    Matrix r = zeros(3);
    r(1) = 7000e3;

    Matrix E = eye(3);

    int n_max = 4;
    int m_max = 4;
    
    Matrix a = AccelHarmonic(r, E, n_max, m_max);
    
    Matrix expected_a(3);
    expected_a(1) = -8.14571105963231; expected_a(2) = 1.8418953912846e-05; expected_a(3) = 6.13947378070986e-05;

    assert(equals(a,expected_a));
}

void AccelHarmonic_test2(){

    Matrix r = zeros(3);
    r(1) = 7000000;

    Matrix E(3,3);
    E(1,1) = -0.984320311916434;   E(1,2) =  0.17638970834414;    E(1,3) = -0.000440838975649208;
    E(2,1) = -0.176389673442133;   E(2,2) = -0.984320409917682;   E(2,3) = -0.000117142922139399;
    E(3,1) = -0.000454589607089469; E(3,2) = -3.75467147037462e-05; E(3,3) =  0.999999895969261;

    int n_max = 20;
    int m_max = 20;
    
    Matrix a = AccelHarmonic(r, E, n_max, m_max);
    
    Matrix expected_a(3);
    expected_a(1) = -8.14573205034458; expected_a(2) = -2.73247143907085e-05; expected_a(3) = -1.83315389744748e-05;

    assert(equals(a,expected_a));
}

void JPL_Eph_DE430_test(){

    double Mjd_TDB = 60000;
    
    auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(Mjd_TDB);
    
    Matrix expected_r_Mercury(3);
    expected_r_Mercury(1) = 1.502618241473265e+11;
    expected_r_Mercury(2) = -1.135593797769126e+11;
    expected_r_Mercury(3) = -0.566320982961168e+11;

    Matrix expected_r_Venus(3);
    expected_r_Venus(1) = 2.072590904061893e+11;
    expected_r_Venus(2) = 0.192804446325880e+11;
    expected_r_Venus(3) = 0.050227573779507e+11;

    Matrix expected_r_Earth(3);
    expected_r_Earth(1) = -1.363821272400698e+11;
    expected_r_Earth(2) = 0.556380040694172e+11;
    expected_r_Earth(3) = 0.241540011325855e+11;

    Matrix expected_r_Mars(3);
    expected_r_Mars(1) = 0.364744403728041e+11;
    expected_r_Mars(2) = 1.449205970590066e+11;
    expected_r_Mars(3) = 0.705336620405834e+11;

    Matrix expected_r_Jupiter(3);
    expected_r_Jupiter(1) = 8.423233002541687e+11;
    expected_r_Jupiter(2) = 1.522290815774233e+11;
    expected_r_Jupiter(3) = 0.477613125702783e+11;

    Matrix expected_r_Saturn(3);
    expected_r_Saturn(1) = 1.376430326229193e+12;
    expected_r_Saturn(2) = -0.761859711270959e+12;
    expected_r_Saturn(3) = -0.369270130577088e+12;

    Matrix expected_r_Uranus(3);
    expected_r_Uranus(1) = 2.111014392571797e+12;
    expected_r_Uranus(2) = 1.950168917610262e+12;
    expected_r_Uranus(3) = 0.826406534869188e+12;

    Matrix expected_r_Neptune(3);
    expected_r_Neptune(1) = 4.589485406921574e+12;
    expected_r_Neptune(2) = -0.398378369693727e+12;
    expected_r_Neptune(3) = -0.275306002090044e+12;

    Matrix expected_r_Pluto(3);
    expected_r_Pluto(1) = 2.578504106591563e+12;
    expected_r_Pluto(2) = -4.169133059035141e+12;
    expected_r_Pluto(3) = -2.043654392630608e+12;

    Matrix expected_r_Moon(3);
    expected_r_Moon(1) = 2.996603981031958e+08;
    expected_r_Moon(2) = 2.166072808518809e+08;
    expected_r_Moon(3) = 0.956951641762235e+08;

    Matrix expected_r_Sun(3);
    expected_r_Sun(1) = 1.350382278564808e+11;
    expected_r_Sun(2) = -0.557048751597339e+11;
    expected_r_Sun(3) = -0.241483564602141e+11;

    assert(equals(r_Mercury, expected_r_Mercury));
    assert(equals(r_Venus, expected_r_Venus));
    assert(equals(r_Earth, expected_r_Earth));
    assert(equals(r_Mars, expected_r_Mars));
    assert(equals(r_Jupiter, expected_r_Jupiter));
    assert(equals(r_Saturn, expected_r_Saturn));
    assert(equals(r_Uranus, expected_r_Uranus));
    assert(equals(r_Neptune, expected_r_Neptune));
    assert(equals(r_Pluto, expected_r_Pluto));
    assert(equals(r_Moon, expected_r_Moon));
    assert(equals(r_Sun, expected_r_Sun));
}

/* --------------- ITERATION 3 FUNCTIONS' TESTS --------------- */

void gast_test(){

    double Mjd_UT1 = 58000;

    double gstime = gast(Mjd_UT1);

    double expected_gstime = 5.991797889524220;

    assert(equals(gstime, expected_gstime));
}

void MeasUpdate_test(){
    
    int n = 6;

    Matrix prior_x(n,1);
    prior_x(1,1) = 7101598.51328984; prior_x(2,1) = 1295244.95471173; prior_x(3,1) = 12755.8818620501;
    prior_x(4,1) = 576.098110709103; prior_x(5,1) = -3084.5123074698; prior_x(6,1) = -6736.03531463327;

    double z = 2653472;

    double g = 2653524.97442074;

    double s = 92.5;

    Matrix G = zeros(6);
    G(1) = 0.484876063686137; G(2) = 0.042004575814763; G(3) = -0.873573590760881;

    Matrix prior_P(6,6);
    prior_P(1,1) = 15877.8626406688;   prior_P(1,2) = -5671.36416769049;    prior_P(1,3) = 8540.82447415922;
    prior_P(1,4) = 48.5595962689329;   prior_P(1,5) = -13.3700378548522;    prior_P(1,6) = 22.4252222768612;

    prior_P(2,1) = -5671.36416769049;  prior_P(2,2) = 24467.3371037644;     prior_P(2,3) = -1495.70201344425;
    prior_P(2,4) = -4.64148232226853;  prior_P(2,5) = 59.5504415186599;     prior_P(2,6) = -26.9419365595934;

    prior_P(3,1) = 8540.82447415922;   prior_P(3,2) = -1495.70201344425;    prior_P(3,3) = 6196.68053320901;
    prior_P(3,4) = 26.7016361772421;   prior_P(3,5) = -4.13117358038685;    prior_P(3,6) = 16.0867106128416;

    prior_P(4,1) = 48.5595962689329;   prior_P(4,2) = -4.64148232226847;    prior_P(4,3) = 26.7016361772421;
    prior_P(4,4) = 0.178295945673018;  prior_P(4,5) = -0.0189362529581429;  prior_P(4,6) = 0.0668595541014411;

    prior_P(5,1) = -13.3700378548522;  prior_P(5,2) = 59.5504415186599;     prior_P(5,3) = -4.13117358038685;
    prior_P(5,4) = -0.0189362529581431;prior_P(5,5) = 0.152611176448901;    prior_P(5,6) = -0.0750233061743933;

    prior_P(6,1) = 22.4252222768611;   prior_P(6,2) = -26.9419365595934;    prior_P(6,3) = 16.0867106128416;
    prior_P(6,4) = 0.0668595541014411; prior_P(6,5) = -0.0750233061743933;  prior_P(6,6) = 0.0845546958716609;

    Matrix K(6,1), x(6,1), P(6,6);
    tie(K,x,P) = MeasUpdate(prior_x,z,g,s,G,prior_P,n);
    
    Matrix expected_K(6,1);
    expected_K(1,1) = -4.80607875684201e-05; expected_K(2,1) = -0.0428209997671326; expected_K(3,1) = -0.137546574808484; 
    expected_K(4,1) = 2.53262106971815e-06; expected_K(5,1) = -3.83873845541371e-05; expected_K(6,1) = -0.000444236157587253; 

    Matrix expected_x(6,1);
    expected_x(1,1) = 7101598.51583584;
    expected_x(2,1) = 1295247.22312939;
    expected_x(3,1) = 12763.1683121753;
    expected_x(4,1) = 576.097976544968;
    expected_x(5,1) = -3084.51027392034;
    expected_x(6,1) = -6736.01178148015;

    Matrix expected_P(6,6);
    expected_P(1,1) = 15877.8626182526;   expected_P(1,2) = -5671.38413996778;    expected_P(1,3) = 8540.76032062828;
    expected_P(1,4) = 48.5595974501807;   expected_P(1,5) = -13.3700557592331;    expected_P(1,6) = 22.4250150792765;

    expected_P(2,1) = -5671.38413996778;  expected_P(2,2) = 24449.5422875578;     expected_P(2,3) = -1552.86125848484;
    expected_P(2,4) = -4.64042985906818;  expected_P(2,5) = 59.5344891481755;     expected_P(2,6) = -27.1265445981635;

    expected_P(3,1) = 8540.76032062828;   expected_P(3,2) = -1552.86125848484;    expected_P(3,3) = 6013.07766506656;
    expected_P(3,4) = 26.7050168248007;   expected_P(3,5) = -4.18241465210703;    expected_P(3,6) = 15.4937257800374;

    expected_P(4,1) = 48.5595974501807;   expected_P(4,2) = -4.64042985906813;    expected_P(4,3) = 26.7050168248007;
    expected_P(4,4) = 0.178295883425745;  expected_P(4,5) = -0.0189353094652347;  expected_P(4,6) = 0.066870472627647;

    expected_P(5,1) = -13.3700557592331;  expected_P(5,2) = 59.5344891481755;     expected_P(5,3) = -4.18241465210703;
    expected_P(5,4) = -0.0189353094652349;expected_P(5,5) = 0.152596875760368;    expected_P(5,6) = -0.0751888002031855;

    expected_P(6,1) = 22.4250150792765;   expected_P(6,2) = -27.1265445981635;    expected_P(6,3) = 15.4937257800374;
    expected_P(6,4) = 0.066870472627647;  expected_P(6,5) = -0.0751888002031855;  expected_P(6,6) = 0.0826395241998163;

    assert(equals(K,expected_K));
    assert(equals(x,expected_x));
    assert(equals(P,expected_P));
}

void G_AccelHarmonic_test(){
    
    Matrix r = zeros(3); 
    r(1) =7000e3;  

    Matrix U = eye(3);                          
    int n_max = 10;                           
    int m_max = 10; 

    Matrix G = G_AccelHarmonic(r,U,n_max,m_max);

    Matrix expected_G(3,3);

    expected_G(1,1) = 0.233053013687368e-5; expected_G(1,2) = 0.000001095301627e-5; expected_G(1,3) = -0.000003125855130e-5;
    expected_G(2,1) = 0.000001095775413e-5; expected_G(2,2) = -0.116371476754752e-5; expected_G(2,3) = -0.000001748808540e-5;
    expected_G(3,1) = -0.000003125939478e-5; expected_G(3,2) = -0.000001748808542e-5; expected_G(3,3) = -0.116681537326909e-5;

    assert(equals(G,expected_G));
}

void GHAMatrix_test(){
    
    double Mjd_UT1 = 51544.5;

    Matrix GHAMat = GHAMatrix(Mjd_UT1);

    Matrix expected_GHAMat(3,3);
    expected_GHAMat(1,1) =  0.181498749692528; expected_GHAMat(1,2) = -0.983391175402774; expected_GHAMat(1,3) =  0.0;
    expected_GHAMat(2,1) =  0.983391175402774; expected_GHAMat(2,2) =  0.181498749692528; expected_GHAMat(2,3) =  0.0;
    expected_GHAMat(3,1) =  0.0; expected_GHAMat(3,2) =  0.0; expected_GHAMat(3,3) =  1.0;

    assert(equals(GHAMat,expected_GHAMat));
}

void Accel_test(){
    
    double x = 58000; 

    Matrix Y = zeros(6);
    Y(1) = 7000e3; Y(5) = 7.5e3;

    Matrix dY = Accel(x, Y);

    Matrix expected_dY(6);
    expected_dY(1) = 0.0; expected_dY(2) = 7.5e3; expected_dY(3) = 0.0; expected_dY(4) = -8.145568813324; expected_dY(5) = -0.000027626103; expected_dY(6) = -0.000059198950;

    assert(equals(dY,expected_dY));
}

void VarEqn_test(){
    
    double x = 0.0;
    Matrix y = zeros(6);
    y(1) = 7000e3; y(5) = 7.5e3;

    Matrix Phi0 = eye(6);

    Matrix yPhi(42);
    for (int j = 1; j <= 6; j++) {
        yPhi(j) = y(j);
        for (int i = 1; i <= 6; i++) {
            yPhi(6*j+i) = Phi0(i, j);  // reshape columna a columna
        }
    }

    Matrix yPhip = VarEqn(x, yPhi);

    Matrix expected_yPhip = zeros(42);
    expected_yPhip(2) = 7500.0; expected_yPhip(4) = -8.14573205034458; expected_yPhip(5) = -2.73247143907085e-05; expected_yPhip(6) = -1.83315389744748e-05; 
    expected_yPhip(10) = 2.33048821485227e-06; expected_yPhip(11) = -2.23210339100888e-11; expected_yPhip(12) = 2.14755080038542e-12; 
    expected_yPhip(16) = -2.23217000439035e-11; expected_yPhip(17) = -1.16365971436494e-06; expected_yPhip(18) = 2.16918839661406e-11;
    expected_yPhip(22) = 2.1458390619955e-12; expected_yPhip(23) = 2.16917594997312e-11; expected_yPhip(24) = -1.16682849732623e-06; 
    expected_yPhip(25) = 1.0; expected_yPhip(32) = 1.0; expected_yPhip(39) = 1.0;

    assert(equals(yPhip,expected_yPhip));
}

/* --------------- ITERATION 4 FUNCTIONS' TESTS --------------- */

void DEInteg_test(){

    double Mjd0 = Mjday(1995,1,29,02,38,0);

    Matrix Y0_apr(6);
    Y0_apr(1) = 6221398.24674587; Y0_apr(2) = 2867713.77142113; Y0_apr(3) = 3006156.19827565; 
    Y0_apr(4) = 4645.04675261818; Y0_apr(5) = -2752.21554475399; Y0_apr(6) = -7507.99862282957;

    Matrix expected_Y(6);
    expected_Y(1) = 5542556.62930487; expected_Y(2) = 3213514.81521648; expected_Y(3) = 3990893.08798422;
    expected_Y(4) = 5394.06783381377; expected_Y(5) = -2365.21310034617; expected_Y(6) = -7061.84483659256;

    Matrix Y = DEInteg(Accel,0,-(obs(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,transpose(Y0_apr));

    assert(equals(Y, expected_Y));
}

void DEInteg_test2(){

    double t = 572.99998998642;
    double t_old = 568.000017106533;

    Matrix Y_old(6);
    Y_old(1) = 7098603.48613637; Y_old(2) = 1310605.81357207; Y_old(3) = 46419.1857559918; 
    Y_old(4) = 613.67034949965;  Y_old(5) = -3077.70988865027; Y_old(6) = -6735.86854200982;

    Matrix expected_Y(6);
    expected_Y(1) = 7101577.66491799; expected_Y(2) = 1295200.03374753; expected_Y(3) = 12739.5577727397;
    expected_Y(4) = 576.005002658814; expected_Y(5) = -3084.62184178477; expected_Y(6) = -6736.02586895252;


    Matrix Y = DEInteg(Accel,0,t-t_old,1e-13,1e-6,6,transpose(Y_old));

    assert(equals(Y, expected_Y));
}

/* --------------- ALL TESTS FUNCTIONS AND MAIN --------------- */

void It0_tests(){
    
    
    cout << "All Iteration 0 tests passed successfully.\n";

}

void It1_tests(){
    
    AccelPointMass_test();
    Cheb3D_test();
    EccAnom_test();
    Frac_test();
    MeanObliquity_test();
    Mjday_test();
    Mjday_test2();
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

void It2_tests(){
    
    EqnEquinox_test();
    LTC_test();
    NutMatrix_test();
    PoleMatrix_test();
    PrecMatrix_test();
    gmst_test();
    AccelHarmonic_test();
    AccelHarmonic_test2();
    JPL_Eph_DE430_test();

    cout << "All Iteration 2 tests passed successfully.\n";

}

void It3_tests(){
    
    gast_test();
    MeasUpdate_test();
    G_AccelHarmonic_test();
    GHAMatrix_test();
    Accel_test();
    VarEqn_test();

    cout << "All Iteration 3 tests passed successfully.\n";

}

void It4_tests(){
    
    DEInteg_test();
    DEInteg_test2();

    cout << "All Iteration 4 tests passed successfully." << endl;
}

int main(){

    int nobs = 46;

	// Carga de archivos
    eop19620101(21413); // Cargar solo las primeras c líneas del archivo eop19620101.txt
	GGM03S(); // Cargamos las matrices Cnm y Snm
	DE430Coeff(); // Cargamos la matriz PC
	GEOS3(nobs);
	
	// AuxParam
	AuxParam.Mjd_UTC = 49746.1163541665;
	AuxParam.Mjd_TT = 49746.1170623147;
	AuxParam.n = 20;
	AuxParam.m = 20;
	AuxParam.sun = 1;
	AuxParam.moon = 1;
	AuxParam.planets = 1;

    It1_tests();
    It2_tests();
    It3_tests();
    It4_tests();

    return 0;
}