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

Param AuxParam;
Matrix eopdata;
Matrix Cnm;
Matrix Snm;
Matrix PC;
Matrix obs;

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

void GGM03S(){
    Cnm = zeros(181, 181);
    Snm = zeros(181, 181);

    FILE *fp = fopen("../data/GGM03S.txt","r");
    if(fp == NULL){
        printf("Failed to open GGM03S.txt file\n");
        exit(EXIT_FAILURE);
    }

    double aux;
    for(int i = i; i <= 181; i++){
        for(int j = 1; j <= i; j++){
            fscanf(fp, "%lf %lf %lf %lf %lf %lf", &aux, &aux, &Cnm(i,j), &Snm(i,j), &aux, &aux);
        }
    }

    fclose(fp);
}

void DE430Coeff(){

    PC = zeros(2285, 1020);
    FILE *fp = fopen("../data/DE430Coeff.txt","r");
    
    if(fp == NULL){
        printf("Failed to open DE430Coeff.txt file\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= 2285; i++){
        
       for(int j = 1; j <= 1020; j++){
            fscanf(fp, "%lf", &PC(i,j));
       }
    }

    fclose(fp);
}

void GEOS3(int f){
    obs = zeros(f, 4);

    FILE *fp = fopen("../data/GEOS3.txt","r");

    if(fp == NULL){
        printf("Failed to open GEOS3.txt file\n");
        exit(EXIT_FAILURE);
    }

    int Y, MO, D, H, MI, S;
    double AZ, EL, DIST;
    char line[55], y[5], mo[3], d[3], h[3], mi[3], s[7], az[9], el[9], dist[10];

    for(int i = 1; i <= f; i++){
        fgets(line, sizeof(line)+2, fp);

        strncpy(y, &(line[0]),4);
        y[4] = '\0';
        Y = atoi(y);

        strncpy(mo, &(line[5]),2);
        mo[2] = '\0';
        MO = atoi(mo);

        strncpy(d, &(line[8]),2);
        d[2] = '\0';
        D = atoi(d);

        strncpy(h, &(line[12]),2);
        h[2] = '\0';
        H = atoi(h);

        strncpy(mi, &(line[15]),2);
        mi[2] = '\0';
        MI = atoi(mi);

        strncpy(s, &(line[18]),6);
        s[6] = '\0';
        S = atoi(s);

        strncpy(az, &(line[25]),8);
        az[8] = '\0';
        AZ = atof(az);
        
        strncpy(el, &(line[35]),8);
        el[8] = '\0';
        EL = atof(el);

        strncpy(dist, &(line[44]),9);
        dist[9] = '\0';
        DIST = atof(dist);

        obs(i,1) = Mjday(Y,MO,D,H,MI,S);
        obs(i,2) = (Rad)*AZ;
        obs(i,3) = (Rad)*EL;
        obs(i,4) = 1e3*DIST;
    } 

    fclose(fp);
}