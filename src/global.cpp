// $Source$
// --------------------------------------------------------------------------------------------------------
// global.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/04/11
//
/** @file global.cpp
 *  @brief eop function implementation
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/global.hpp"

Matrix eopdata;

Param AuxParam;
Matrix Cnm;
Matrix Snm;
Matrix PC;

void eop19620101(int c){
    eopdata = zeros(13,c);

    FILE *fp = fopen("../data/eop19620101.txt","r");
    
    if(fp == NULL){
        printf("Failed to open eop19620101.txt file\n");
        exit(EXIT_FAILURE);
    }

    for(int j = 1; j <= c; j++){
        fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &(eopdata(1,j)),&(eopdata(2,j)),&(eopdata(3,j)),&(eopdata(4,j)),
        &(eopdata(5,j)),&(eopdata(6,j)),&(eopdata(7,j)),&(eopdata(8,j)),&(eopdata(9,j)),&(eopdata(10,j)),&(eopdata(11,j)),&(eopdata(12,j)),&(eopdata(13,j)));
    }

    fclose(fp);
}