// $Source$
// --------------------------------------------------------------------------------------------------------
// It2_tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file It2_tests.cpp
 *  @brief Tests for all iteration 2 functions
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>

#include "../include/EqnEquinox.hpp"
#include "../include/LTC.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/gmst.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/JPL_Eph_DE430.hpp"

using namespace std;

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


void It2_tests(){
    
    EqnEquinox_test();
    LTC_test();
    NutMatrix_test();
    PoleMatrix_test();
    PrecMatrix_test();
    gmst_test();
    AccelHarmonic_test();
    JPL_Eph_DE430_test();

    cout << "All Iteration 2 tests passed successfully.\n";

}