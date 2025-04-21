// $Source$
// --------------------------------------------------------------------------------------------------------
// timediff.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file timediff.cpp
 *  @brief Implementation of the timediff function.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/timediff.hpp"

void timediff(double UT1_UTC, double TAI_UTC,
              double &UT1_TAI, double &UTC_GPS, double &UT1_GPS,
              double &TT_UTC, double &GPS_UTC) {

    const double TT_TAI = 32.184;   // TT - TAI
    const double GPS_TAI = -19.0;   // GPS - TAI

    double TT_GPS  = TT_TAI - GPS_TAI;
    double TAI_GPS = -GPS_TAI;
    UT1_TAI = UT1_UTC - TAI_UTC;
    double UTC_TAI = -TAI_UTC;
    UTC_GPS = UTC_TAI - GPS_TAI;
    UT1_GPS = UT1_TAI - GPS_TAI;
    TT_UTC  = TT_TAI - UTC_TAI;
    GPS_UTC = GPS_TAI - UTC_TAI;
}
