// $Header$
// --------------------------------------------------------------------------------------------------------
// MeanObliquity.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/19
//
/** @file MeanObliquity.hpp
 *  @brief Computes the mean obliquity of the ecliptic from the Modified Julian Date (TT).
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _MEANOBLIQUITY_HPP
#define _MEANOBLIQUITY_HPP

/** 
 * @brief Computes the mean obliquity of the ecliptic.
 * 
 * @param Mjd_TT Modified Julian Date (Terrestrial Time)
 * @return Mean obliquity of the ecliptic in radians
 */
double MeanObliquity(double Mjd_TT);

#endif // MEANOBLIQUITY_HPP
