// $Header$
// --------------------------------------------------------------------------------------------------------
// Mjday.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file Mjday.hpp
 *  @brief Computes the Modified Julian Date from a calendar date and time.
 * 
 * Converts Gregorian calendar date and time to Modified Julian Date (MJD).
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _MJDAY_
#define _MJDAY_

/**
 * @brief Computes the Modified Julian Date (MJD) from calendar date and time.
 * 
 * @param year  Year (e.g., 2024)
 * @param mon   Month (1-12)
 * @param day   Day of the month (1-31)
 * @param hr    Hour (default = 0)
 * @param min   Minute (default = 0)
 * @param sec   Second (default = 0)
 * @return Modified Julian Date (MJD)
 */
double Mjday(int year, int mon, int day, int hr = 0, int min = 0, int sec = 0);

#endif // _MJDAY_
