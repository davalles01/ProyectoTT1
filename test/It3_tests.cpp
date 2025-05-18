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
    
    int n = 6;

    Matrix prior_x(n,1);
    prior_x(1,1) = 7101598.51328984; prior_x(2,1) = 1295244.95471173; prior_x(3,1) = 12755.8818620501;
    prior_x(4,1) = 576.098110709103; prior_x(5,1) = -3084.5123074698; prior_x(6,1) = -6736.03531463327;

    double z = 2653472;

    double g = 2653524.97442074;

    double s = 92.5;

    Matrix G = zeros(6);
    G(1) = 0.484876063686137; G(2) = 0.042004575814763; G(3) = -0.873573590760881;

    Matrix prior_P(6,6);
    prior_P(1,1) = 15877.8626406688;   prior_P(1,2) = -5671.36416769049;    prior_P(1,3) = 8540.82447415922;
    prior_P(1,4) = 48.5595962689329;   prior_P(1,5) = -13.3700378548522;    prior_P(1,6) = 22.4252222768612;

    prior_P(2,1) = -5671.36416769049;  prior_P(2,2) = 24467.3371037644;     prior_P(2,3) = -1495.70201344425;
    prior_P(2,4) = -4.64148232226853;  prior_P(2,5) = 59.5504415186599;     prior_P(2,6) = -26.9419365595934;

    prior_P(3,1) = 8540.82447415922;   prior_P(3,2) = -1495.70201344425;    prior_P(3,3) = 6196.68053320901;
    prior_P(3,4) = 26.7016361772421;   prior_P(3,5) = -4.13117358038685;    prior_P(3,6) = 16.0867106128416;

    prior_P(4,1) = 48.5595962689329;   prior_P(4,2) = -4.64148232226847;    prior_P(4,3) = 26.7016361772421;
    prior_P(4,4) = 0.178295945673018;  prior_P(4,5) = -0.0189362529581429;  prior_P(4,6) = 0.0668595541014411;

    prior_P(5,1) = -13.3700378548522;  prior_P(5,2) = 59.5504415186599;     prior_P(5,3) = -4.13117358038685;
    prior_P(5,4) = -0.0189362529581431;prior_P(5,5) = 0.152611176448901;    prior_P(5,6) = -0.0750233061743933;

    prior_P(6,1) = 22.4252222768611;   prior_P(6,2) = -26.9419365595934;    prior_P(6,3) = 16.0867106128416;
    prior_P(6,4) = 0.0668595541014411; prior_P(6,5) = -0.0750233061743933;  prior_P(6,6) = 0.0845546958716609;

    Matrix K(6,1), x(6,1), P(6,6);
    tie(K,x,P) = MeasUpdate(prior_x,z,g,s,G,prior_P,n);
    
    Matrix expected_K(6,1);
    expected_K(1,1) = -4.80607875684201e-05; expected_K(2,1) = -0.0428209997671326; expected_K(3,1) = -0.137546574808484; 
    expected_K(4,1) = 2.53262106971815e-06; expected_K(5,1) = -3.83873845541371e-05; expected_K(6,1) = -0.000444236157587253; 

    Matrix expected_x(6,1);
    expected_x(1,1) = 7101598.51583584;
    expected_x(2,1) = 1295247.22312939;
    expected_x(3,1) = 12763.1683121753;
    expected_x(4,1) = 576.097976544968;
    expected_x(5,1) = -3084.51027392034;
    expected_x(6,1) = -6736.01178148015;

    Matrix expected_P(6,6);
    expected_P(1,1) = 15877.8626182526;   expected_P(1,2) = -5671.38413996778;    expected_P(1,3) = 8540.76032062828;
    expected_P(1,4) = 48.5595974501807;   expected_P(1,5) = -13.3700557592331;    expected_P(1,6) = 22.4250150792765;

    expected_P(2,1) = -5671.38413996778;  expected_P(2,2) = 24449.5422875578;     expected_P(2,3) = -1552.86125848484;
    expected_P(2,4) = -4.64042985906818;  expected_P(2,5) = 59.5344891481755;     expected_P(2,6) = -27.1265445981635;

    expected_P(3,1) = 8540.76032062828;   expected_P(3,2) = -1552.86125848484;    expected_P(3,3) = 6013.07766506656;
    expected_P(3,4) = 26.7050168248007;   expected_P(3,5) = -4.18241465210703;    expected_P(3,6) = 15.4937257800374;

    expected_P(4,1) = 48.5595974501807;   expected_P(4,2) = -4.64042985906813;    expected_P(4,3) = 26.7050168248007;
    expected_P(4,4) = 0.178295883425745;  expected_P(4,5) = -0.0189353094652347;  expected_P(4,6) = 0.066870472627647;

    expected_P(5,1) = -13.3700557592331;  expected_P(5,2) = 59.5344891481755;     expected_P(5,3) = -4.18241465210703;
    expected_P(5,4) = -0.0189353094652349;expected_P(5,5) = 0.152596875760368;    expected_P(5,6) = -0.0751888002031855;

    expected_P(6,1) = 22.4250150792765;   expected_P(6,2) = -27.1265445981635;    expected_P(6,3) = 15.4937257800374;
    expected_P(6,4) = 0.066870472627647;  expected_P(6,5) = -0.0751888002031855;  expected_P(6,6) = 0.0826395241998163;

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

void VarEqn_test(){
    
    double x = 0.0;
    Matrix y = zeros(6);
    y(1) = 7000e3; y(5) = 7.5e3;

    Matrix Phi0 = eye(6);

    Matrix yPhi(42);
    for (int j = 1; j <= 6; j++) {
        yPhi(j) = y(j);
        for (int i = 1; i <= 6; i++) {
            yPhi(6*j+i) = Phi0(i, j);  // reshape columna a columna
        }
    }

    Matrix yPhip = VarEqn(x, yPhi);

    Matrix expected_yPhip = zeros(42);
    expected_yPhip(2) = 7500.0; expected_yPhip(4) = -8.14573205034458; expected_yPhip(5) = -2.73247143907085e-05; expected_yPhip(6) = -1.83315389744748e-05; 
    expected_yPhip(10) = 2.33048821485227e-06; expected_yPhip(11) = -2.23210339100888e-11; expected_yPhip(12) = 2.14755080038542e-12; 
    expected_yPhip(16) = -2.23217000439035e-11; expected_yPhip(17) = -1.16365971436494e-06; expected_yPhip(18) = 2.16918839661406e-11;
    expected_yPhip(22) = 2.1458390619955e-12; expected_yPhip(23) = 2.16917594997312e-11; expected_yPhip(24) = -1.16682849732623e-06; 
    expected_yPhip(25) = 1.0; expected_yPhip(32) = 1.0; expected_yPhip(39) = 1.0;

    assert(equals(yPhip,expected_yPhip));
}

void It3_tests(){
    
    //gast_test();
    MeasUpdate_test();
    //G_AccelHarmonic_test();
    //GHAMatrix_test();
    //Accel_test();
    //VarEqn_test();

    cout << "All Iteration 3 tests passed successfully.\n";

}