// $Source$
// --------------------------------------------------------------------------------------------------------
// Accel.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file Accel.cpp
 *  @brief Source file for the Accel function implementation
 *
 *  Computes the acceleration of an Earth-orbiting satellite due to:
 *  - the Earth's harmonic gravity field,
 *  - the gravitational perturbations of the Sun and Moon,
 *  - the solar radiation pressure,
 *  - the atmospheric drag.
 *
 *
 *  @author Daniel Vallés Belloso
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Accel.hpp"

Matrix Accel(double x, Matrix Y){
    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,AuxParam.Mjd_UTC + x/86400,'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    double Mjd_UT1 = AuxParam.Mjd_UTC + x/86400 + UT1_UTC/86400;
    double Mjd_TT = AuxParam.Mjd_UTC + x/86400 + TT_UTC/86400;
    
    Matrix P = PrecMatrix(MJD_J2000,Mjd_TT);;
    Matrix N = NutMatrix(Mjd_TT);
    Matrix T = N * P;
    Matrix GHA_T = GHAMatrix(Mjd_UT1) * T;
    Matrix E = PoleMatrix(x_pole,y_pole) * GHA_T;

    double MJD_TDB = Mjday_TDB(Mjd_TT);
    auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(MJD_TDB);
    
    Matrix Y_13 = extract_vector(Y,1,3);
    Matrix a = AccelHarmonic(Y_13, E, AuxParam.n, AuxParam.m);
    
    if (AuxParam.sun){
        Matrix a_sun = AccelPointMass(Y_13,r_Sun,GM_Sun);
        a = a + a_sun;
    }

    if (AuxParam.moon){
        Matrix a_moon = AccelPointMass(Y_13,r_Moon,GM_Moon);
        a = a + a_moon;
    }

    if (AuxParam.planets){
        Matrix a_Mercury = AccelPointMass(Y_13,r_Mercury,GM_Mercury);
        Matrix a_Venus = AccelPointMass(Y_13,r_Venus,GM_Venus);
        Matrix a_Mars = AccelPointMass(Y_13,r_Mars,GM_Mars);
        Matrix a_Jupiter = AccelPointMass(Y_13,r_Jupiter,GM_Jupiter);
        Matrix a_Saturn = AccelPointMass(Y_13,r_Saturn,GM_Saturn);
        Matrix a_Uranus = AccelPointMass(Y_13,r_Uranus,GM_Uranus);
        Matrix a_Neptune = AccelPointMass(Y_13,r_Neptune,GM_Neptune);
        Matrix a_Pluto = AccelPointMass(Y_13,r_Pluto,GM_Pluto);
        a = a + a_Mercury;
        a = a + a_Venus;
        a = a + a_Mars;
        a = a + a_Jupiter;
        a = a + a_Saturn;
        a = a + a_Uranus;    
        a = a + a_Neptune;
        a = a + a_Pluto;
    }
    
    return union_vector(extract_vector(Y,4,6),a);
}
