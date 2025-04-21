// $Header$
// --------------------------------------------------------------------------------------------------------
// timediff.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file timediff.hpp
 *  @brief Computes time differences between various time scales.
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _TIMEDIFF_
#define _TIMEDIFF_

/**
 * @brief Computes differences between time scales.
 *
 * @param UT1_UTC Difference between UT1 and UTC [s].
 * @param TAI_UTC Difference between TAI and UTC [s].
 * @param UT1_TAI Output: Difference between UT1 and TAI [s].
 * @param UTC_GPS Output: Difference between UTC and GPS [s].
 * @param UT1_GPS Output: Difference between UT1 and GPS [s].
 * @param TT_UTC  Output: Difference between TT and UTC [s].
 * @param GPS_UTC Output: Difference between GPS and UTC [s].
 */
void timediff(double UT1_UTC, double TAI_UTC,
              double &UT1_TAI, double &UTC_GPS, double &UT1_GPS,
              double &TT_UTC, double &GPS_UTC);

#endif // _TIMEDIFF_
