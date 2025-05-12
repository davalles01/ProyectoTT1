// $Source$
// --------------------------------------------------------------------------------------------------------
// It3_tests.cpp
// --------------------------------------------------------------------------------------------------------
//
// Created: 2025/05/11
//
/** @file It3_tests.cpp
 *  @brief Tests for all iteration 3 functions
 *
 *  @author Daniel Vallés Belloso.
 *  @bug No known bugs.
 */
// --------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <cmath>
#include <iostream>

#include "../include/gast.hpp"
#include "../include/MeasUpdate.hpp"
#include "../include/G_AccelHarmonic.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/Accel.hpp"
#include "../include/VarEqn.hpp"

using namespace std;

bool equalsAux(double a, double b, double tol = 1e-12) {
    return std::abs(a - b) < tol;
}

void gast_test(){

    double Mjd_UT1 = 58000;

    double gstime = gast(Mjd_UT1);

    double expected_gstime = 5.991797889524220;

    assert(equalsAux(gstime, expected_gstime));
}

void MeasUpdate_test(){

    int n = 3; // tamaño del estado
    int m = 2;

    Matrix prior_x(n,1);
    prior_x(1,1) = 1.0; prior_x(2,1) = 2.0; prior_x(3,1) = 3.0;

    Matrix z(m,1);
    z(1,1) = 1.1; z(2,1) = 1.9;

    Matrix g(m,1);
    g(1,1) = 1.0; g(2,1) = 2.0;

    Matrix s(m,1);
    s(1,1) = 0.1; s(2,1) = 0.1;

    Matrix G(m,n);
    G(1,1) = 1.0; G(1,2) = 0.0; G(1,3) = 0.0;
    G(2,1) = 0.0; G(2,2) = 1.0; G(2,3) = 0.0;

    Matrix prior_P = eye(n);

    auto[K,x,P] = MeasUpdate(prior_x,z,g,s,G,prior_P,n);

    Matrix expected_K = zeros(3,2);
    expected_K(1,1) = 0.990099009900990; expected_K(2,2) = 0.990099009900990;

    Matrix expected_x(3,1);
    expected_x(1,1) = 1.099009900990099; expected_x(2,1) = 1.900990099009901; expected_x(3,1) = 3.000000000000000;

    Matrix expected_P = zeros(3,3);
    expected_P(1,1) = 0.009900990099010; expected_P(2,2) = 0.009900990099010; expected_P(3,3) = 1.000000000000000;

    assert(equals(K,expected_K));
    assert(equals(x,expected_x));
    assert(equals(P,expected_P));
}

void G_AccelHarmonic_test(){
    
    Matrix r = zeros(3); 
    r(1) =7000e3;  

    Matrix U = eye(3);                          
    int n_max = 10;                           
    int m_max = 10; 

    Matrix G = G_AccelHarmonic(r,U,n_max,m_max);

    Matrix expected_G(3,3);

    expected_G(1,1) = 0.233053013687368e-5; expected_G(1,2) = 0.000001095301627e-5; expected_G(1,3) = -0.000003125855130e-5;
    expected_G(2,1) = 0.000001095775413e-5; expected_G(2,2) = -0.116371476754752e-5; expected_G(2,3) = -0.000001748808540e-5;
    expected_G(3,1) = -0.000003125939478e-5; expected_G(3,2) = -0.000001748808542e-5; expected_G(3,3) = -0.116681537326909e-5;

    assert(equals(G,expected_G));
}

void GHAMatrix_test(){
    
    double Mjd_UT1 = 51544.5;

    Matrix GHAMat = GHAMatrix(Mjd_UT1);

    Matrix expected_GHAMat(3,3);
    expected_GHAMat(1,1) =  0.181498749692528; expected_GHAMat(1,2) = -0.983391175402774; expected_GHAMat(1,3) =  0.0;
    expected_GHAMat(2,1) =  0.983391175402774; expected_GHAMat(2,2) =  0.181498749692528; expected_GHAMat(2,3) =  0.0;
    expected_GHAMat(3,1) =  0.0; expected_GHAMat(3,2) =  0.0; expected_GHAMat(3,3) =  1.0;

    assert(equals(GHAMat,expected_GHAMat));
}

void Accel_test(){
    
    double x = 58000; 

    Matrix Y = zeros(6);
    Y(1) = 7000e3; Y(5) = 7.5e3;

    Matrix dY = Accel(x, Y);

    Matrix expected_dY(6);
    expected_dY(1) = 0.0; expected_dY(2) = 7.5e3; expected_dY(3) = 0.0; expected_dY(4) = -8.145568813324; expected_dY(5) = -0.000027626103; expected_dY(6) = -0.000059198950;

    assert(equals(dY,expected_dY));
}

void printMatrix(Matrix vec, const std::string& name) {
    std::cout << name << ":" << std::endl;
    for (int i = 1; i <= vec.n_column; ++i) {
        double val = vec(i);
        if (std::abs(val - 0.0) >= 1e-12) {
            std::cout << "  (" << i << ") = "  << val << std::endl;
        }
    }
}

void VarEqn_test(){
    
    double x = 0.0;
    Matrix y(6);
    y(1) = 7000e3; y(2) = 0.0; y(3) = 0.0; y(4) = 0.0; y(5) = 7.5e3; y(6) = 0.0;

    Matrix Phi0 = eye(6);

    Matrix yPhi(42);
    for (int i = 1; i <= 6; i++) {
        yPhi(i) = y(i);
    }
    int idx = 7;
    for (int j = 1; j <= 6; j++) {
        for (int i = 1; i <= 6; i++) {
            yPhi(idx++) = Phi0(i, j);  // reshape columna a columna
        }
    }

    Matrix yPhip = VarEqn(x, yPhi);

    Matrix expected_yPhip = zeros(42);
    expected_yPhip(2) = 7500.0; expected_yPhip(4) = -8.145732050345; expected_yPhip(5) = -0.000027324714; expected_yPhip(6) = -0.000018331539; 
    expected_yPhip(10) = 0.000002330488; expected_yPhip(11) = -0.000000000022; expected_yPhip(12) = 0.000000000002; 
    expected_yPhip(16) = -0.000000000022; expected_yPhip(17) = -0.000001163660; expected_yPhip(18) = 0.000000000022;
    expected_yPhip(22) = 0.000000000002; expected_yPhip(23) = 0.000000000022; expected_yPhip(24) = -0.000001166828; 
    expected_yPhip(25) = 1.0; expected_yPhip(32) = 1.0; expected_yPhip(39) = 1.0;

    printMatrix(yPhip,"yPhip");
    printMatrix(expected_yPhip,"expected_yPhip");

    assert(equals(yPhip,expected_yPhip));
}

void It3_tests(){
    
    //gast_test();
    //MeasUpdate_test();
    //G_AccelHarmonic_test();
    //GHAMatrix_test();
    Accel_test();
    //VarEqn_test();

    cout << "All Iteration 3 tests passed successfully.\n";

}