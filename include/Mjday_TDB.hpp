// $Header$
// --------------------------------------------------------------------------------------------------------
// Mjday_TDB.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/20
//
/** @file Mjday_TDB.hpp
 *  @brief Computes the Modified Julian Date for barycentric dynamical time (TDB).
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _MJDAY_TDB_HPP
#define _MJDAY_TDB_HPP

/**
 * @brief Computes the Modified Julian Date for barycentric dynamical time.
 * 
 * @param Mjd_TT Modified Julian Date in Terrestrial Time (TT)
 * @return Modified Julian Date in Barycentric Dynamical Time (TDB)
 */
double Mjday_TDB(double Mjd_TT);

#endif // _MJDAY_TDB_HPP
