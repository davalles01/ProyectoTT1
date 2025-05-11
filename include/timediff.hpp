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

#include "matrix.hpp"

/**
 * @brief Computes differences between time scales.
 *
 * @param UT1_UTC Difference between UT1 and UTC [s].
 * @param TAI_UTC Difference between TAI and UTC [s].
 * @return tuple<double, double, double, double, double>: 
 *  UT1_TAI  Difference between UT1 and TAI [s].
 *  UTC_GPS  Difference between UTC and GPS [s].
 *  UT1_GPS  Difference between UT1 and GPS [s].
 *  TT_UTC   Difference between TT and UTC [s].
 *  GPS_UTC  Difference between GPS and UTC [s].
 */
tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC);

#endif 
