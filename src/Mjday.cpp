// $Source$
// --------------------------------------------------------------------------------------------------------
// Mjday.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Mjday.cpp
 *  @brief Implementation of function to compute Modified Julian Date (MJD).
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/Mjday.hpp"
#include <cmath>

double Mjday(int year, int mon, int day, int hr, int min, int sec) {

    double jd = 367.0 * year
              - std::floor((7 * (year + std::floor((mon + 9) / 12.0))) * 0.25)
              + std::floor(275 * mon / 9.0)
              + day + 1721013.5
              + (((sec / 60.0 + min) / 60.0 + hr) / 24.0);

    return jd - 2400000.5;
}
