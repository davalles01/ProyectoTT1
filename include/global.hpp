// $Header$
// --------------------------------------------------------------------------------------------------------
// global.hpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file global.hpp
 *  @brief eop function declaration to extract data from the eop matrix
 * 
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#ifndef _GLOBAL_
#define _GLOBAL_

#include "matrix.hpp"
#include <cmath>

typedef struct{
    double Mjd_UTC, Mjd_TT;
    int n, m, sum, moon, planets;
} Param;

extern Param AuxParam;
extern Matrix eopdata;
extern Matrix Cnm;
extern Matrix Snm;
extern Matrix PC;

/**
 * @brief Extracts data from the eop matrix
 *
 * @param c Number of columns to extract
 */
void eop19620101(int c);

/**
 * @brief Extracts data from the GGM03S matrix
 */
void GGM03S();

#endif