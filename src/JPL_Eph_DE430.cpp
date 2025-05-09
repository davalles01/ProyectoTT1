// $Source$
// --------------------------------------------------------------------------------------------------------
// JPL_Eph_DE430.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/09
//
/** @file JPL_Eph_DE430.cpp
 *  @brief JPL_Eph_DE430 function implementation. Computes the sun, moon, and nine major planets' equatorial position using JPL Ephemerides
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include "../include/JPL_Eph_DE430.hpp"

//tuple<Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix, Matrix> 
Matrix JPL_Eph_DE430(double Mjd_TDB){

    DE430Coeff(); // Cargamos la matriz PC

    double JD = Mjd_TDB + 2400000.5;

    int i;
    for(i = 1; i <= PC.n_row; i++){
        if(PC(i,1) <= JD && JD <= PC(i,2)){
            break;
        }
    }
    Matrix PCtemp = extract_row(PC, i);

    double t1 = PCtemp(1)-2400000.5; 

    double dt = Mjd_TDB - t1;

    Matrix temp = zeros(4);
    for(int j = 0; j < 4; j++){
        temp(j+1) = 231 +13*j;
    }
    Matrix Cx_Earth = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix Cy_Earth = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix Cz_Earth = extract_vector(PCtemp,temp(3),temp(4)-1);
    temp = temp + 39;
    Matrix Cx = extract_vector(PCtemp,temp(1),temp(2)-1);
    Matrix Cy = extract_vector(PCtemp,temp(2),temp(3)-1);
    Matrix Cz = extract_vector(PCtemp,temp(3),temp(4)-1);
    Cx_Earth = union_vector(Cx_Earth,Cx);
    Cy_Earth = union_vector(Cy_Earth,Cy);
    Cz_Earth = union_vector(Cz_Earth,Cz);
    int j;
    double Mjd0;
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }else{
        if(16<dt && dt<=32){
            j=1;
            Mjd0 = t1+16*j;
        }
    }

    Matrix r_Earth_aux = Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+16, extract_vector(Cx_Earth, 13*j+1,13*j+13),extract_vector(Cy_Earth, 13*j+1,13*j+13), extract_vector(Cz_Earth, 13*j+1,13*j+13));
    Matrix r_Earth = transpose(r_Earth_aux)*1e3;
    
    return r_Earth;
}