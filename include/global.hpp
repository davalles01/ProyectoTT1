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
#include "Mjday.hpp"
#include <string.h>
#include "SAT_Const.hpp"

using namespace consts;

typedef struct{
    double Mjd_UTC, Mjd_TT;
    int n, m, sun, moon, planets;
} Param;

extern Param AuxParam;
extern Matrix eopdata;
extern Matrix Cnm;
extern Matrix Snm;
extern Matrix PC;
extern Matrix obs;

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

/**
 * @brief Extracts data from the DE430Coeff matrix
 */
void DE430Coeff();

/**
 * @brief Extracts data from the GEOS3.txt file
 */
void GEOS3(int f);


#endif