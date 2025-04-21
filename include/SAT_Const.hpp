// $Header$
// --------------------------------------------------------------------------------------------------------
// SAT_Const.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file SAT_Const.hpp
 *  @brief Definition of astronomical and mathematical constants.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _SAT_CONST_
#define _SAT_CONST_

namespace consts {

    // Mathematical constants
    inline constexpr double pi2  = 6.28318530717958647692; // 2*pi
    inline constexpr double Rad  = 0.01745329251994329577; // pi/180
    inline constexpr double Deg  = 57.2957795130823208772; // 180/pi
    inline constexpr double Arcs = 206264.8062470963552;   // 3600*180/pi

    // General
    inline constexpr double MJD_J2000 = 51544.5;
    inline constexpr double T_B1950   = -0.500002108;
    inline constexpr double c_light   = 299792458.0;           // [m/s]
    inline constexpr double AU        = 149597870700.0;        // [m]

    // Physical parameters of the Earth, Sun and Moon
    inline constexpr double R_Earth = 6378136.3;                // [m]
    inline constexpr double f_Earth = 1.0 / 298.257223563;      // flattening
    inline constexpr double R_Sun   = 696000000.0;              // [m]
    inline constexpr double R_Moon  = 1738000.0;                // [m]

    inline constexpr double omega_Earth = 15.04106717866910 / 3600.0 * Rad; // [rad/s]

    // Gravitational coefficients [m^3/s^2]
    inline constexpr double GM_Earth   = 398600.435436e9;
    inline constexpr double GM_Sun     = 132712440041.9394e9;
    inline constexpr double GM_Moon    = GM_Earth / 81.30056907419062;
    inline constexpr double GM_Mercury = 22031.78e9;
    inline constexpr double GM_Venus   = 324858.592e9;
    inline constexpr double GM_Mars    = 42828.375214e9;
    inline constexpr double GM_Jupiter = 126712764.8e9;
    inline constexpr double GM_Saturn  = 37940585.2e9;
    inline constexpr double GM_Uranus  = 5794548.6e9;
    inline constexpr double GM_Neptune = 6836527.10058e9;
    inline constexpr double GM_Pluto   = 977.0000000000009e9;

    // Solar radiation pressure at 1 AU [N/m^2]
    inline constexpr double P_Sol = 1367.0 / c_light;

}

#endif // _SAT_CONST_
