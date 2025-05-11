// $Source$
// --------------------------------------------------------------------------------------------------------
// MeanObliquity.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file MeanObliquity.cpp
 *  @brief Implementation of the mean obliquity of the ecliptic calculation.
 *
 *  Uses polynomial expressions in Julian centuries from J2000.
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/MeanObliquity.hpp"
#include "../include/SAT_Const.hpp"
#include "../include/constants.hpp"

using namespace consts;
using namespace constants;

double MeanObliquity(double Mjd_TT) {

    double T = (Mjd_TT - MJD_J2000) / 36525.0;

    double seconds = 84381.448 - (46.8150 + (0.00059 - 0.001813 * T) * T) * T;

    return (seconds / 3600.0) * pi / 180.0;
}
